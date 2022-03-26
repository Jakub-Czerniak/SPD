#ifndef PROCESSLIST_HPP
#define PROCESSLIST_HPP

class processList
{
private:
    int processCount;
    int **processData;
public:
    processList();
    processList(std::istream& data);
    processList(const processList& pL);
    ~processList();
    processList operator=(const processList& pL)
    {
        for(int i=0;i<processCount;i++)
            delete processData[i];
        delete processData;
    
        processCount=pL.processCount;
    
            processData= new int*[processCount];
        for(int i=0;i<processCount;i++)
            processData[i]=new int[4];
        for (int i = 0; i < processCount; i++)
            for (int j = 0; j < 4; j++)
            {
                if(j==0)
                processData[i][j]=i;
                else
                processData[i][j]=pL.processData[i][j];
            }               
    
        return *this;
    }

    void optimaze();
    void display();
};


#endif
