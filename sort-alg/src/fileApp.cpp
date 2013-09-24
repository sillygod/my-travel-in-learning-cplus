//fileApp.cpp

#include "fileApp.h"
#include <cstdio>
fileApp::fileApp(char *InFileName, char*OutFileName,char *SortMode)
:fileLength(0),totalword(0),mReadBuffer(NULL),mWordNode(NULL),mAlgorithm(NULL)
{
    mInFileName=InFileName;
    mOutFileName=OutFileName;
    mSortMode=SortMode;
}

bool fileApp::SetupApp()
{

    mInputFile.open(mInFileName, ios::binary);

    if(!mInputFile) //error
    {
        cout<<"open file error";
        return false;
    }

    mInputFile.seekg(0,ios::end);
    fileLength=mInputFile.tellg();      //get the size of the file
    mInputFile.seekg(0,ios::beg);

    mReadBuffer=new char [fileLength+1]; // +1 for the '\0'

    mInputFile.read(mReadBuffer,fileLength); //read data in buffer
    *(mReadBuffer+fileLength)='\0';

    mInputFile.close(); //close file


    return true; //successful
}

fileApp::~fileApp() //call EndApp ?
{
    EndApp();
    delete mAlgorithm;
    delete [] mWordNode;
    delete [] mReadBuffer;
}

void fileApp::BeginApp()
{
    timeBegin=clock();
    mOutputFile.open(mOutFileName,ios::out);
    // analyze and sort and show
    AnalyzeWord(); //here , we get the total word num

    mAlgorithm= new algorithm(totalword,mSortMode);
    mAlgorithm->sort(mWordNode);
    mAlgorithm->WriteData(mOutputFile);

    mOutputFile.close();

    timeEnd=clock();
}

void fileApp::EndApp()
{

    cout<<"Time cost="<<(timeEnd-timeBegin)/(double)CLOCKS_PER_SEC<<" second";
    cout<<"\npress any key to continue...";
    getchar();
}


void fileApp::cutSymbol()
{
    bool ignoreSymbol   =false; //without ' ' '\n'
    char *pignoreSymbol =NULL;
    char *index         =NULL;

    index=mReadBuffer;

    while(index!=(mReadBuffer+fileLength)) //analyze the character before '\0', delete special character without ' ' '\n'
    {
        if(*(index)==' ' || *(index)=='\n')
            totalword++;

        if( !( *(index)>64 && *(index)<91 ) && !( *(index)>96 && *(index)<123 )
           && !(*(index)==' ' || *(index)=='\n') )
        {
            if(!ignoreSymbol)
            {
                ignoreSymbol=true;
                pignoreSymbol=index;
                if(*(index+1)=='\0')
                {
                    strcpy(index,index+1);
                    break;
                }
            }
        }
        else
        {
            if(ignoreSymbol)
            {

                strcpy(pignoreSymbol,index);
                index=pignoreSymbol;
                ignoreSymbol=false;
            }
        }
        index++;
    }

    /*
        index--;
        if( !( *(index)>64 && *(index)<91 ) && !( *(index)>96 && *(index)<123 )&& !(*(index)==' ' || *(index)=='\n') )
            *(index)='\0'; //the last punctuation
*/
}


void fileApp::AnalyzeWord()
{
    int Row             = 1; //use '\n' to judge
    int Column          = 1; //use ' '  to judge , here column means the order of words
    char *index         =NULL;
    char *StringHead    =NULL;
    bool stringStart    =false;

    index=mReadBuffer;

    cutSymbol(); //delete the special symbol without ' ', '\n'

    mWordNode=new Node [totalword]; // here, totalword is temporary to be the words' number
    totalword=0;


    while(index!=(mReadBuffer+fileLength))
    {
        if(*(index)=='\0')
            break;
        if(*(index)!=' ' && *(index)!='\n')
        {
            if(!stringStart)
            {
                stringStart=true;
                StringHead=index;
            }

        }

        if(*(index)==' ')
        {
            *(index)='\0';
            if(stringStart)
            {
                mWordNode[totalword].mColumn    =Column;
                mWordNode[totalword].mRow       =Row;
                mWordNode[totalword].mStringHead=StringHead;
                mWordNode[totalword].mStringTail=index;

                totalword++;
                StringHead=NULL;
                stringStart=false;
                Column++;
            }
        }

        if(*(index)=='\n')
        {
            *(index)='\0';
            if(stringStart)
            {
                mWordNode[totalword].mColumn    =Column;
                mWordNode[totalword].mRow       =Row;
                mWordNode[totalword].mStringHead=StringHead;
                mWordNode[totalword].mStringTail=index;

                stringStart=false;
                totalword++;
                StringHead=NULL;
            }
            Row++;
            Column=1;
        }
        index++;
    }

    if(stringStart) // int the while loop, the last word isn't added
    {
        mWordNode[totalword].mColumn    =Column;
        mWordNode[totalword].mRow       =Row;
        mWordNode[totalword].mStringHead=StringHead;
        mWordNode[totalword].mStringTail=index;

        stringStart=false;
        totalword++;
        StringHead=NULL;
    }
    //the mReadBuffer  remains the alphabet and \0
}
