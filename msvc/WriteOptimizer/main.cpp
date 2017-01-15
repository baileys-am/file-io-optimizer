#pragma warning(disable:4996)
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <vector>
#include <numeric>

int main()
{
	std::vector<size_t> bufferSizes = { 256, 512, 1024, 2048, 4096 };
	bufferSizes.resize(5);
	std::vector<long long> totalTimes;
	std::vector<char> buffer;

	for (size_t i = 0; i < bufferSizes.size(); i++)
	{
		// Initialize buffer
		buffer.resize(bufferSizes[i]);
		std::iota(std::begin(buffer), std::end(buffer), 0);

		// Open file
		FILE* filePointer;
		filePointer = fopen("outfile.bin", "wb");

		// Caculate write properties
		size_t elementSize = sizeof(buffer.front());
		size_t elementCount = buffer.size();

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

		// Save total time
		totalTimes.push_back(totalTime);

		// Output run info
		std::cout << "Write speed of " << (1e9 * bufferSizes[i]) / (1e9 * totalTime) << " B/s using buffer size of " << bufferSizes[i] << std::endl;
	}

	getchar();
	return 0;
}