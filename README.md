# Hamming_8_4
В программе реализованы функции кодирования вектора из 4 битовых значений к 8 битовым значениям и декодироравния из 8 битовых значений возвращения к 4 бытовым.



Инструкция для работы с программой:
1. После запуска программа принимает целое число от 1 до 2^64-1.
2. Потом выводится список команд: Составить вектор (1), кодирование (2), декодирование (3), инвертировать бит в кодированном векторе (4), ввести новое значение (5), выход (6). Потом программа требут ввода целого числа (номер команды).
3. Команды:

3.1. Составление вектора, берет добавленное в начале программы целое число и переведет в двоичном представлении, дополнить ведущими нулями пока его длина не делится на 4 без остатка. И составляя из полученного результата вектор из 4 бытовых значений, вохвращает полученный вектор.

3.2.Кодирование, берет результать команды составления вектора и возвращает вектор из 8 битовых значениях, каждый i-ый элемент которого кодированное значение для i-го элемента результата команды составления вектора. Когда мы вызываем кодирования, когда вектор 4 битовых значений не составлен, тогда программа требует сначала вызвать команду составления вектора.

3.3. Декодирование, обратное к кодированию и возвращает вектор 4 битовых значений. И точно так же, когда вызывается до вызова кодирования, программа требует сначала кодировать.

3.4. Инвертация бита, если кодированный вектор содержить больше одного значения, то программа требует номер элемента вектора от 1 до размера вектора и номер бита от 1 до 8. И инвертирует соответствующий бит.

3.5. Ввести новое значение, пользователь таким образом пользователь может изменить введенное в начало число.

3.6. Выход, пока не будет выбрана команда выход, программа будет спрашивать команду.
