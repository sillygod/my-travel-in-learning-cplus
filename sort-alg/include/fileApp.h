//fileApp.h
#ifndef FILEAPP_H
#define FILEAPP_H

#include "main.h"
#include "Node.h"
#include "algorithm.h"



class fileApp
{
    public:
        fileApp(char *InFileName, char*OutFileName,char *SortMode);
        ~fileApp();
        bool SetupApp(); //open file and read data in buffer
        void AnalyzeWord();
        void cutSymbol();

        void BeginApp();
        void EndApp();

    private:
        int          fileLength;
        int          totalword; // count whether it is the same word or not
        std::ifstream     mInputFile;
        std::ofstream     mOutputFile;
        char        *mSortMode;
        char        *mInFileName;
        char        *mOutFileName;
        char        *mReadBuffer;
        Node        *mWordNode;
        algorithm   *mAlgorithm;
        double       timeBegin;
        double       timeEnd;
};

#endif // FILEAPP_H
