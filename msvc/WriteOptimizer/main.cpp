#pragma warning(disable:4996)
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <vector>
#include <numeric>

int main()
{
    size_t numberOfTrials = 1000;
    std::vector<size_t> bufferSizes = { 256, 512, 1024, 2048, 4096, 8192, 16384, 32678 };
    std::vector<long long> totalTimes(bufferSizes.size());
    std::vector<long long> trialTimes(numberOfTrials);
    std::vector<char> buffer;

    for (size_t i = 0; i < bufferSizes.size(); i++)
    {
        // Initialize buffers
        buffer.resize(bufferSizes[i]);
        std::iota(std::begin(buffer), std::end(buffer), 0);

        // Caculate write properties
        size_t elementSize = sizeof(buffer.front());
        size_t elementCount = buffer.size();

        for (size_t j = 0; j < numberOfTrials; j++)
        {
            // Open file
            FILE* filePointer;
            filePointer = fopen("outfile.bin", "wb");

            // Get start time
            auto startTime = std::chrono::high_resolution_clock::now();

            // Perform write test
            fwrite(&buffer.front(), elementSize, elementCount, filePointer);

            // Get end time
            auto endTime = std::chrono::high_resolution_clock::now();

            // Close file
            fclose(filePointer);

            // Calcualte total time
            auto totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

            // Save trial time
            trialTimes[j] = totalTime;
        }

        // Average trials
        float averageTime = std::accumulate(trialTimes.begin(), trialTimes.end(), 0.0) / trialTimes.size();

        // Save total time
		totalTimes[i] = averageTime;

        // Output run info
        std::cout << "Write speed of " << ((float)bufferSizes[i] / 1e6) / (averageTime * 1e-9) << " MB/s using buffer size of " << bufferSizes[i] << std::endl;
    }

    getchar();
    return 0;
}