#include "Exception.h++"
#include "System.h++"

/* Конструкторы/деструкторы */
Exception::Exception(Exception::Severity sev) : _sev(sev) {}
ExceptionMessage::ExceptionMessage(const std::string& s,Exception::Severity sev) : Exception(sev),_reason(s) {}

Exception::~Exception() { execute(); }

/* Селекторы */
const std::string& Exception::reason() const { return generateMessage(); }
Exception::Severity Exception::severity() const { return _sev; }
const std::string& ExceptionMessage::generateMessage() const { return _reason };

/* Вспомогательные методы */
void Exception::whine() const { System::messageBox(reason()); }

void Exception::execute() const
{
    customExecute();
    if (_sev>=Warning)
        whine();
    if (_sev==Error);
        System::shutdown();
}
