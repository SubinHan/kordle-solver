#include "KordleEntropyStrategy.h"
#include "KordleMachine.h"
#include <cmath>
#include <future>
#include <iostream>
#include <thread>
#include <unordered_set>

// 익명 네임스페이스로 헬퍼 함수와 결과 구조체 정의
namespace {
    // average 점수와 인덱스 쌍
    using ScoreIndex = pair<double,int>;

    struct LocalResult {
        // 이 청크에서의 상위 5개 (average, index)
        vector<ScoreIndex> topEntries;
    };

    // [start, end) 범위 평가: 상위 5개 average,index 반환
    LocalResult evaluateChunk(
        const vector<wstring>& queryableWords,
        const vector<wstring>& validWords,
        size_t                 start,
        size_t                 end)
    {
        vector<ScoreIndex> scores;
        scores.reserve(end - start);

        // 각 단어마다 average 계산
        for (size_t i = start; i < end; ++i)
        {
            int score = 0;
            for (const auto& valid : validWords)
            {
                KordleResult result = KordleMachine::queryKordle(queryableWords[i], valid);
                for (auto color : result.result)
                {
                    if (color == KordleColor::YELLOW) score += 1;
                    else if (color == KordleColor::GREEN) score += 5;
                }
            }
            double average = static_cast<double>(score) / validWords.size();
            scores.emplace_back(average, static_cast<int>(i));
        }

        // 내림차순 정렬 후 상위 5개 추출
        sort(scores.begin(), scores.end(),
             [](auto& a, auto& b){ return a.first > b.first; });

        LocalResult res;
        for (size_t k = 0; k < scores.size() && k < 5; ++k)
            res.topEntries.push_back(scores[k]);
        return res;
    }
}


wstring KordleEntropyStrategy::calculateNextWord(vector<wstring> validWords, vector<wstring> queryableWords, int countQueried)
{
#define PARALLEL
#ifdef PARALLEL
    return calculateNextWordParallel(validWords, queryableWords, countQueried);
#else
	if (validWords.empty())
		return wstring();

	//if (countQueried == 0)
	//{
	//	return FIRST_BEST;
	//}

	if (validWords.size() < 30)
	{
		queryableWords = validWords;
	}

	double max = 0;
	int maxIndex = -1;
	//vector<wstring> test;
	//test.push_back(L"ㄱㅓㅁㅇㅏㄴ");
	//test.push_back(L"ㅇㅏㄴㄱㅏㅣ");
    const double invValidWordsSize = 1.0 / validWords.size();

	for (size_t i = 0; i < queryableWords.size(); ++i)
	{
		int score = 0;

		for (vector<wstring>::iterator iter2 = validWords.begin(); iter2 != validWords.end(); iter2++)
		{
			KordleResult result = KordleMachine::queryKordle(queryableWords[i], *iter2);
			for (KordleColor color : result.result)
			{
				if (color == KordleColor::YELLOW)
				{
					score++;
				}
				if (color == KordleColor::GREEN)
				{
					score += 5;
				}
			}
		}
		double average = score * invValidWordsSize;
		if (average > max)
		{
			max = average;
			maxIndex = i;
		}
	}

	return queryableWords.at(maxIndex);
#endif
}

wstring KordleEntropyStrategy::calculateNextWordParallel(vector<wstring> validWords, vector<wstring> queryableWords, int countQueried)
{
	if (validWords.empty())
		return wstring();

	//if (countQueried == 0)
	//{
	//	return FIRST_BEST;
	//}

	if (validWords.size() < 30)
	{
		queryableWords = validWords;
	}
	
    const size_t total = queryableWords.size();
    if (total == 0)
        return wstring();

    // 하드웨어 스레드 수 또는 최소 2
    unsigned int threadCount = thread::hardware_concurrency();
    if (threadCount == 0) threadCount = 2;
    // 청크 크기 계산
    size_t blockSize = (total + threadCount - 1) / threadCount;

    // 비동기 작업들을 보관할 future 컨테이너
    vector<future<LocalResult>> futures;
    futures.reserve(threadCount);

    // 각 청크별로 evaluateChunk 호출
    for (unsigned int t = 0; t < threadCount; ++t)
    {
        size_t start = t * blockSize;
        size_t end   = min(start + blockSize, total);
        if (start >= end) break;

        futures.emplace_back(
            async(launch::async,
                  evaluateChunk,
                  cref(queryableWords),
                  cref(validWords),
                  start,
                  end));
    }
     // 모든 청크의 상위 5개를 합쳐 전체 상위 5개 추출
    vector<ScoreIndex> allScores;
    for (auto& f : futures)
    {
        LocalResult lr = f.get();
        allScores.insert(allScores.end(),
                         lr.topEntries.begin(),
                         lr.topEntries.end());
    }
    sort(allScores.begin(), allScores.end(),
         [](auto& a, auto& b){ return a.first > b.first; });

    // 중복 인덱스를 걸러내면서 상위 5개 선택
    vector<ScoreIndex> finalTop;
    unordered_set<int> seen;
    for (auto& si : allScores)
    {
        if (seen.insert(si.second).second)  // 새 인덱스일 때만
            finalTop.push_back(si);
        if (finalTop.size() == 5) break;
    }

    // 결과 출력
    wcout << L"=== 상위 5 후보 ===\n";
    for (size_t rank = 0; rank < finalTop.size(); ++rank)
    {
        double avg = finalTop[rank].first;
        int    idx = finalTop[rank].second;
        wcout << L"#" << (rank+1)
              << L": \"" << queryableWords[idx]
              << L"\" (점수: " << avg << L")\n";
    }

    // 최고 1개의 단어를 반환
    if (!finalTop.empty())
        return queryableWords[ finalTop[0].second ];
    else
        return wstring();
}

Cloneable* KordleEntropyStrategy::clone()
{
	return new KordleEntropyStrategy();
}