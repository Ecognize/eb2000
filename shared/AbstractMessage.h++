#ifndef _EB2K_ABSTRACT_MESSAGE_
#define _EB2K_ABSTRACT_MESSAGE_

#include <iostream>

class AbstractMessage
{
    public:
        /* Операции ввода-вывода в поток */
        // TODO: возможно композитное поведение
        void readFromStream(std::istream& str)
        {
            _readFromStream(&str);
        }
        
        void writeToStream(std::ostream& str)
        {
            _writeToStream(&str);
        }
        
        /* Игровое время измеряется в миллисекундах */ 
        unsigned int issueTime() const { return _issueTime; }
        
    protected:
        virtual void _readFromStream(std::istream& str)=0;
        virtual void _writeToStream(std::ostream& str)=0;
        
        unsigned int _issueTime;
};

std::istream& operator>>(std::istream &str,AbstractMessage& msg)
{
    msg.readFromStream(str);
    return str;
}

std::ostream& operator<<(std::ostream &str,const AbstractMessage& msg)
{
    msg.writeToStream(str);
    return str;
}

#endif