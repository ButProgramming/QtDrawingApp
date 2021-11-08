# QtDrawingApp
Данное приложение было создано в результате выполнения тестового задания для компании "ОМП Систем".

## About
Приложение представляет собой простое средство рисования. Всего на выбор доступно 3 фигуры: эллипс, прямоугольник и треугольник. Данные фигуры можно соединять связывающей линией, которая не разрушается при передвижении фигур, с которыми она была связана. К тому же имеется возможность сохранения и загрузки рисунка из файла .qda.

## How to run
Для запуска приложения Вам необходимо установить Qt Creator. Запуск возможен на Windows и Ubuntu.

### Windows
1. Скачайте [Qt Online Installer](https://www.qt.io/download-qt-installer?hsCtaTracking=99d9dd4f-5681-48d2-b096-470725510d34%7C074ddad0-fdef-4e53-8aa8-5e8a876d6ab4) (ссылка рабочая на момент написания данного руководства).
2. В установщике выберите версию Qt Creator (например 5.12.2), а также загрузите MSVC 2019 и MinGW.
3. Склонируйте проект в Вашу папку. Например: 
```bash
cd C:\Users\Admin\Desktop\qt
```
```bash
git clone https://github.com/ButProgramming/QtDrawingApp
```
4. Необходимо зайти в папку с проектом и открыть QtDrawingApp.pro.
5. Сконфигурировать проект в Qt Creator.

### Ubuntu
1. [Установите Qt](https://stackoverflow.com/questions/48147356/install-qt-on-ubuntu)
2. Откройте Qt Creator
3. File -> Open File or Project -> Ваша папка -> QtDrawingApp.pro

## Others
1. Приложение собирается как для х32-, так и для х64-битной операционной системы (Windows или Ubuntu). 
2. Для конфигурации проекта на Windows у Вас должен быть установлен MSVC (версия автора - MSVC 2019 32 бит).