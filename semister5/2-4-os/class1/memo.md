問題 1
このプログラムを実行すると以下の文字列が出力された。

```
I am a student.
I major in Informatics.
```

ここで、プログラムの 7 行目を

```
write(1, "I am a student.\n",10);
```

と書き換えると出力は次のように変わった。

```
I am a stuI major in Informatics.
```

また、同じくプログラムの 7 行目を

```
write(1, "I am a student.\n",100);
```

と書き換えると出力は次のように変わった。

```
I am a student.
I major in Informatics.
4����h���� ����0���P����I major in Informatics.
```

ここで、プログラムをコンパイルするときに以下の警告文が出た。

```
test.c: In function ‘main’:
test.c:6:10: warning: ‘write’ reading 100 bytes from a region of size 17 [-Wstringop-overread]
    6 |          write(1,"I am a student.\n",100);
      |          ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
In file included from test.c:2:
/usr/include/unistd.h:378:16: note: in a call to function ‘write’ declared with attribute ‘access (read_only, 2, 3)’
  378 | extern ssize_t write (int __fd, const void *__buf, size_t __n) __wur
      |                ^~~~~
```

さらには自身でバッファ(配列)を定義して、そのバッファにいくつか文字列を格納したうえで write を実行する関数を実行した。実行したプログラムは以下のプログラムである。

```
#include <stdio.h>
#include <unistd.h>
int
main(int argc, char **argv)
{
         char buf[16];
         buf[0] = 'c';
         buf[1] = 'd';
         buf[15] = '\n';
         write(STDIN_FILENO, buf,16);
         write(2,"I major in Informatics.\n",24);
         return 0;
}
```

この実行結果は以下のものである。

```
cd      /�d
I major in Informatics.
```

以上の実行結果を踏まえて、write 関数とは、第 2 引数に読み込むバッファ、第 3 引数に何バイト分バッファの情報を読み込むかの情報を入れることで、バッファの情報を出力する関数であると考えられる。なお、第 1 引数に関してはは IBM の write 関数のドキュメントよりファイルまたはソケットの記述子であることがわかる。
