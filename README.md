# Расчет данных с гироскопа и визуализация

## Описание проекта

Необходимо разработать приложение, получающее данные гироскопа и рассчитывающее ориентацию устройства с их помощью.
Данные гироскопа представляют собой мгновенные угловые скорости вокруг трех строительных осей. Для получения углового положения (ориентации)
устройства следует проинтегрировать угловые скорости по времени. При этом необходима информация о том, в каком положении находилось устройство на
момент подключения.

В рамках проекта гироскоп используется для вычисления относительного углового перемещения устройства с момента подключения. При
этом, в силу дискретного характера данных, интегрирование можно заменить на суммирование.

Для обеспечения возможности корректного определения ориентации, сервер опрашивает гироскоп, снабжает измерения гироскопа временем в миллисекундах с
момента старта приложения и отправляет полученный пакет подключенным клиентам. Формат пакета представлен в таблице ниже.

Время | X | Y | Z
--- | --- | --- | --- |
int, 4 Б | float, 4 Б | float, 4 Б | float, 4 Б

X, Y и Z в пакете — это угловые скорости вращения вокруг соответствующих осей (показания гироскопа).
Сервер автоматически рассылает пакет подключенным клиентам. Никаких дополнительных команд не требуется.

Устройство можно схематично изобразить в виде прямоугольного параллелепипеда, повернутого на рассчитанные углы.

В проекте используется стенд на основе контроллера OpenPilot CC3D со сторонней прошивкой. Прошивка опрашивает оборудование, установленное на плате (гироскоп, акселерометр и
датчик температуры) и отправляет эти данные в последовательный порт, функционирующий поверх шины USB. Контроллер подключается к компьютеру со
специальным программным обеспечением, которое считывает данные с контроллера и рассылает их при помощи сервера, работающего поверх протокола TCP.

Схема стенда приведена на рисунке ниже.

![stand_scheme](https://github.com/niksuf/GyroscopeCalculations/blob/master/img/stand_scheme.png)

TCP-сервер представлен программой accel (рисунок ниже). Для запуска сервера необходимо нажать на кнопку «Открыть» справа от полей ввода портов TCP/IP. В
панели «Сырые данные» отображаются данные от устройства. Панель «Обработка» показывает обработанные данные. Левая нижняя часть окна отображает трехмерную визуализацию 
устройства. Фиолетовая линия показывает направление вектора ускорения.

![accel_window](https://github.com/niksuf/GyroscopeCalculations/blob/master/img/accel_window.png)

При тестировании проекта в удаленном формате, TCP-сервер остается без изменений, однако исходными данными являются не показания устройства OpenPilot CC3D, а файл с 
записанными показаниями данного устройства. При проведении тестирования доступны различные файлы с экспериментальными данными:
  *```still.c3d``` – устройство лежит неподвижно.
  *```turn*.c3d``` – устройство поворачивается вокруг указанной оси.
  *```shift*.c3d``` – устройство сдвигается вдоль указанной оси без поворота.
  *```drop*.c3d``` – устройство роняют с небольшой высоты на ровную горизонтальную поверхность.
  *```joystick.c3d``` – устройство наклоняют на небольшие углы относительно горизонтали, имитируя работу джойстиком.
  *```quick*.c3d``` – устройство быстро перемещается и вращается случайным образом, после чего возвращается в исходное положение.

Для воспроизведения файла необходимо указать его путь на вкладке «Из файла» вручную, либо при помощи диалога, вызываемого по кнопке «...», после чего нажать на 
кнопку «воспроизведение» правее поля ввода.

При отсутствии устройства или файла доступен ввод данных с устройства напрямую в поля ax, ay, az, gx, gy и gz.
