#ifndef DATE_H
#define DATE_H

class Date
{
public:
    static const unsigned int monthsPerYear = 12;
    //months in a year
    explicit Date( int = 1, int =1 ,int = 1900);
    //default constructor;
    void print( ) const;//打印日期

    ~Date();

private :
    unsigned int month ;
    unsigned int day ;
    unsigned int year;

    unsigned int checkDay ( int ) const;

};

#endif