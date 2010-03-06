// TODO: Заголовочный комментарий сюда
#ifndef _EB2K_EXCEPTION_HPP_
#define _EB2K_EXCEPTION_HPP_

#include <string>

/* Базовый класс исключений, определяет интерфейс и (частично) поведение исключений */
class Exception
{
    public:
        /* Серьезность ошибки: отладочное сообщение, предупреждение, ошибка */
        enum Severity { Debug=0,Warning,Critical; }
        
        /* Конструктор заполяет поля, деструктор приводит в исполнение действие исключения */
        Exception(Severity);
        ~Exception();
        
        /* Селекторы */
        const std::string& reason() const;  // Причина
        Severity severity() const;          // Серьезность
        
    private:
        /* А в private ли их? */
        void whine() const;     // Выкинуть окно сообщения
        void execute() const;   // Отладочное сообщение: ничего не делать
                                // Предупреждение: показать окно сообщения
                                // Ошибка: показать окно сообщения, завершить работу
        Severity _sev; 
        
    protected:
        /* Виртуальный интерфейс для наследников */
        virtual const string& generateMessage() const =0;  // Вернуть итоговое сообщение пользователю
        virtual void customExecute() {};                    // Особые действия во время «исполнения исключения»
};

/* Класс исключения с простым текстовым сообщением. Скорее пример, чем нужный класс */
class ExceptionMessage
{
    public:
        ExceptionMessage(const std::string&,Severity s=Exception::Warning);
    private:
        std::string _reason;
        const std::string& generateMessage() const;   
};

#endif
