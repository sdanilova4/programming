# programming
## на 3
1) Используем git status, чтобы узнать, на какой ветке мы находимся.

![alt text](skrin/1.png)

2) Как выглядит git log:

![alt text](skrin/2.png)

3) Создадим файл sort.c и вставим туда код функции сортировки:

![alt text](skrin/3.png)

4) Сейчас вывод git status выглядит так:

![alt text](skrin/4.png)

5) Добавим файл в область stage (add) 
6) Сейчас вывод git status выглядит так:

![alt text](skrin/5-6.png)

7) Закоммитим файл в репозиторий.
8) Сейчас вывод git status выглядит так:

![alt text](skrin/7-8.png)

9) Добавим комментарий с любым текстом в этот же файл

![alt text](skrin/9.png)

10)  Сейчас вывод git status выглядит так:

![alt text](skrin/10.png)

11)  Добавим (add) изменение файла 
12)  Сейчас вывод git status выглядит так:

![alt text](skrin/11-12.png)

13)  Изменим файл еще раз (добавим еще комментарий)

![alt text](skrin/13.png)

14)  Сделаем коммит

![alt text](skrin/14.png) 

15)  Сейчас вывод git status и журнал (log) выглядят так:

![alt text](skrin/15.png) 

16)  Добавим в stage и закоммитим последнее изменение

![alt text](skrin/16.png)

17)  Запушим на удаленный репо (git push)

![alt text](skrin/17.png)

### Работа с ветками

1. Используем git branch mybranch, чтобы создать новую ветку с именем mybranch.
2. Снова используем git branch, чтобы увидеть новую созданную ветку: 

![alt text](<skrin/vetki/Снимок экрана 2025-11-24 100505.png>)

3. Используем git switch mybranch (можно было и git checkout mybranch), чтобы переключиться на новую ветку:

![alt text](<skrin//vetki/Снимок экрана 2025-11-24 100611.png>)

4. Изменение вывода git status при переключении между master и новой веткой:

![alt text](<skrin/vetki/Снимок экрана 2025-11-24 100742.png>)

5. Убеждаемся, что мы находимся на своей ветке mybranch, прежде чем продолжить.

![alt text](skrin/vetki/v5.png)

6. Создадим файл с именем file1.txt и своим именем. 
7. Добавим файл и закоммитьте это изменение.

![alt text](skrin/vetki/v6-7.png)

8. Использовав git log --oneline --graph, видим, что наша ветка указывает на новый коммит.

![alt text](<skrin/vetki/Снимок экрана 2025-11-24 101428.png>)

9. Вернемся к ветке с именем master.
10. Используем git log --oneline --graph 
11. Создадим новый файл с именем file2.txt и закоммитим его. 
12. Используем git log --oneline --graph --all, чтобы увидеть, что наша ветка указывает на новый коммит, и что теперь у двух веток разные коммиты.

![alt text](skrin/vetki/v11.png) 

13. Переключимся на ветку mybranch. 
14. видим, что file2.txt пропал
15. Используем git diff mybranch main, чтобы увидеть разницу между двумя ветками

![alt text](<skrin/vetki/Снимок экрана 2025-11-24 102704.png>)

16. Закоммитим и запушим на удаленный репо ветку mybranch (git push -u origin mybranch)

![alt text](<skrin/vetki/Снимок экрана 2025-11-24 104608.png>)

17.  Убедимся, что в github.com две ветки master и mybranch, не забыв запушить изменения master ветки в master

![alt text](<skrin/vetki/Снимок экрана 2025-11-24 104100.png>)

## на 4

1. Переключимся на ветку mybranch. В ней находится файл sort.c из 
предыдущих шагов с функцией сортировки 
2. Перезапишим содержимое в sort.c, добавив функцию main(), в которой 
будет объявлен массив из нескольких чисел (int array[]={...}) и 
вызвана функция сортировки для этого массива: 

![alt text](<skrin/na_4/part_1/Снимок экрана 2025-11-28 103856.png>)

3. git diff вывел: 

![alt text](<skrin/na_4/part_1/Снимок экрана 2025-11-28 104217.png>)

4. diff --staged? Пустой?

5. Добавим в staged файл sort.c
6. git diff вывел: 
7. git diff --staged вывел:

![alt text](<skrin/na_4/part_1/Снимок экрана 2025-11-28 104644.png>)

8. Удалим одно число в массиве в sort.c: 
9. git diff вывел: 
10. git diff --staged вывел:

![alt text](<skrin/na_4/part_1/Снимок экрана 2025-11-28 104900.png>)
![alt text](<skrin/na_4/part_1/Снимок экрана 2025-11-28 104914.png>)

11. Объясните, что происходит 

12. Запустим git status и обратим внимание, что sort.c присутствует дважды 
в выводе:

![alt text](<skrin/na_4/part_1/Снимок экрана 2025-11-28 104952.png>)

13. Запустим git restore --staged sort.c, чтобы отменить индексацию 
изменения 
14. вывод git status выглядит так:

![alt text](<skrin/na_4/part_1/Снимок экрана 2025-11-28 105045.png>)

15. Индексируем изменение (add) и сделайте коммит:

![alt text](<skrin/na_4/part_1/Снимок экрана 2025-11-28 111821.png>)

16. журнал выглядит так: 

![alt text](<skrin/na_4/part_1/Снимок экрана 2025-11-28 114600.png>)

17. Добавим в sort.c в main() printf(“hello git\n”);. 
18. содержимое sort.c:

![alt text](<skrin/na_4/part_1/Снимок экрана 2025-11-28 114725.png>)

19. вывод git status выглядит так

![alt text](<skrin/na_4/part_1/Снимок экрана 2025-11-28 114807.png>)

20. Запустите git restore sort.c 
21. содержимое sort.c:

![alt text](<skrin/na_4/part_1/Снимок экрана 2025-11-28 115932.png>)

22. вывод git status выглядит так

![alt text](<skrin/na_4/part_1/Снимок экрана 2025-11-28 114807.png>)

23. Запушим на удаленный репо ветку.

## ветки и ff-merge

1. Создим файл greeting.txt, проиндексировав его и закоммитив с 
сообщением “Add file greeting.txt”. 
2. Добавим в этот файл слово hello, индексируем и коммитим с текстом 
"Add content to greeting.txt" :

![alt text](<skrin/na_4/part_2/Снимок экрана 2025-11-28 120616.png>)
![alt text](<skrin/na_4/part_2/Снимок экрана 2025-11-28 121011.png>)

3. Создаим ветку с именем feature/uppercase.
4. Переключимся на эту ветку 
5. вывод git status выглядит так 

![alt text](<skrin/na_4/part_2/Снимок экрана 2025-11-28 121256.png>)

6. Отредактируем greeting.txt, чтобы он содержал приветствие в верхнем регистре (HELLO) 
7. Добавим файл greeting.txt и закоммитим
8. вывод git branch:

![alt text](<skrin/na_4/part_2/Снимок экрана 2025-11-28 121428.png>)


9. вывод git log --oneline --graph –all: 

![alt text](<skrin/na_4/part_2/Снимок экрана 2025-11-28 121549.png>)

10. Переключимся на главную ветку 
11. Используем cat, чтобы увидеть содержимое файла greetings.txt 
12. Сравним ветки(diff)

13. Объединим ветки:

![alt text](<skrin/na_4/part_2/Снимок экрана 2025-11-28 122608.png>)

14. Используем cat, чтобы увидеть содержимое файла greetings.txt 
15. Удалим ветку с заглавными буквами (feature/uppercase)

![alt text](<skrin/na_4/part_2/Снимок экрана 2025-11-28 123101.png>)

16. Смержим ветку mybranch в master (git merge) 

![alt text](<skrin/na_4/part_2/Снимок экрана 2025-11-28 124105.png>)

17. вывод git log --oneline --graph –all: 

![alt text](<skrin/na_4/part_2/Снимок экрана 2025-11-28 123937.png>)

18. Запушим изменения ветки master на удаленный репо.

