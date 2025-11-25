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
