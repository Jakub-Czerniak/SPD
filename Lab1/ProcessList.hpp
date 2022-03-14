#ifndef PROCESSLIST_HPP
#define PROCESSLIST_HPP

class processList
{
private:
    int processCount;   //number of processes to optimize  
    int **processTimes; //matrix of 3 x processCount 
    
public:
    processList();
    processList(const processList& pL);//copy constructor
    processList(std::istream& data);
    ~processList();
    processList operator=(const processList& pL)
    {
        for(int i=0;i<processCount;i++)
            delete processTimes[i];
        delete processTimes;
    
        processCount=pL.processCount;
    
            processTimes= new int*[processCount];
        for(int i=0;i<processCount;i++)
            processTimes[i]=new int[3];
        for (int i = 0; i < processCount; i++)
            for (int j = 0; j < 3; j++)
                processTimes[i][j]=pL.processTimes[i][j];
    
        return *this;
    }

    void addLine(int a, int b, int c); //adds line of process times to the furthest row
    void display(); //displays matrix of processTimes
    void connect(processList front, processList middle, processList back); //merges three process lists back into one 
    void sortSmallest(int column); //sort processTimes from smallest to highest by specified column values
    void sortHighest(int column);
    int timeOnMachine();//returns time in which all processes will be finished 
    void optimize();//optimazes time spend on machine of the whole process
};


#endif