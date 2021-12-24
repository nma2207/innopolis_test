# Тестовое задание

Нужно было сделать клиент серверное приложение для решения некоторой простой алгоритмической задачи

## Что было сделано

### Клиент и сервер
Для клиента и сервера были реализованы абстрактные классы `Server` и `Client` соответственно. Созданы дочерние классы `TcpServer`, `UdpServer` и `TcpClient`, `UdpClient`. Внутри них был применен паттерн "Шаблонный метод", т.е. подключение, отправка и получение сообщений были разделены по шагам, общие методы реализованы в абстрактном классе, а особенности реализации для UDP и TCP были выведены в дочерние классы.

### Обработка сообщений на стороне сервера
Для возможности легкой замены текущего алгоритма на другой был использован паттерн "Стратегия", т.е. выполнение алгоритма выведено в отдельный класс и в случае необходимости, можно его заменить. Реализован абстактный класс `StringProcessor` и его дочерний клас `NumbersProcessor`. Логика работы алгоритма простая: делим входящую строку на подстроки по регулярному выражению, далее полученные числа переводим в тип `int`, сортируем, вычисляем сумму и помещаем в две строки, которые далее отправляются клиенту

### Тестирование
Было реализовано тестирование класса `NumbersProcessor` при помощи фреймворка `GoogleTest`. 

## Запуск
Для запуска сервера необходимо ввести следующее
```
> (project_path)/server/build/server TYPE PORT_NUMBER
```
Где `TYPE` - тип сервера TCP или UDP, `PORT_NUMBER` - номер порта.


Для запуска клиента:
```
> (project_path)/client/build/client TYPE SERVER_IP PORT_NUMBER
```
Где `TYPE` - TCP или UDP, `SERVER_IP` - ip-адресс сервера, `PORT_NUMBER` - номер порта.

Далее будет предложено ввести сообщение, которое отправится на сервер и будет получен ответ.

Например

```
> 10 banan 1 orange 5 water
1 5 10
16
```
