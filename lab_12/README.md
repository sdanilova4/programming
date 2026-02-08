### 0) собираем многофайловый проект:
``` 
gcc main.c coffeehouse.c -o app -I.
```
Опция -I указывает путь к папке с заголовочными файлами

На выходе мы получим один готовый исполняемый файл с именем app
#
# build static lib

### 1) получаем объектные файлы (.o)

```
gcc -c main.c

gcc -c coffeehouse.c
```

### 2) линковка (связывание этих файлов в один бинарный файл)
```
gcc main.o coffeehouse.o
```
### 3) Сборка и линковка библиотеки
``` 
ar rc libCOFFEE.a coffeehouse.o

gcc main.o -o coffe_exe -L. -lCOFFE

./coffe_exe
```
ar - команда для архивации
lib - префикс, COFFEE - имя библиотеки, а .a расширение
#
# build dynamic lib

### сборка
```
gcc main.c -c

gcc coffeehouse.c -c -fPIC

gcc --shared main.o coffeehouse.o -o libCOFFEE.so
```

### линковка и запуск
```
gcc main.o -o dynamic_exe -L. -lCOFFEE -Wl,-rpath,.

./dynamic_exe
```
-Wl - вызов линковщика, -rpath - путь где искать библиотеку, он вшит в исполняемый файл, '.' - искать в текущем каталоге