using namespace std;
#ifndef Time_H
#define Time_H

class Time 
{
public:
    explicit Time( int = 0, int = 0, int = 0);

    //set Functions 
    void setTime(int,int,int);
    void setHour( int );
    void setMinute( int );
    void setSecond( int );

    //get Functions 
    unsigned int getHour() const;
    unsigned int getMinute() const ;
    unsigned int getSecond() const ;


    void printUniversal() const;
    void printStandard() const;
private:
    unsigned int hour;
    unsigned int minute;
    unsigned int second;
};
#endif

