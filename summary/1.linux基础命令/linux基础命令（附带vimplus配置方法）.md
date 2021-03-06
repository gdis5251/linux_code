# ```linux```基础命令

## 1.为什么在自己的电脑上装```linux```时需要装字符界面而不要图形界面？

我们看```windows```或```macOS```的操作系统的界面多么漂亮多么流畅，但是为什么```linux```操作系统的图形界面..emm...不知道怎么说，那么到底是为什么呢？难道```linux```没有人给弄吗？并不是的，应该说```linux```不需要。

1. 首先```linux```面向的用户是程序猿或者是懂电脑的人的。
2. ```linux```基本上都是用在服务器上的，而服务器需要高效的操作系统。
3. 既然```linux```用在服务器上，那么就需要操作系统尽可能小的占用内存嘛。所以字符界面占用内存小。
4. 那么服务器只有一个呀，那么如果有10个人同时要用这个系统怎么办？总不能一个用完另一个再去用吧。那么就有了一个终端软件```XShell```来远程控制。如果是图形界面，如果要穿图形，就会出现远程访问卡顿的问题。所以为了避免这个问题，就用字符界面。
5. 而且字符界面可以用命令或```shell```脚本来进行自动化的批量操作。

其实说了这么多点，我们为什么要装字符界面？**为了适应公司！！**人家公司是字符界面，你总不能不用吧。

## 2.`linux`的基本命令

> 下列只是基本常用的命令，并且选项也只是常用的。如果在使用中遇到问题，就是用man 这个命令，要学会自己解决问题。

### 1. ls

**语法：** ls [选项] [目录或文件]

**功能：**如果ls [选项] [目录] 将会列出该目录下的所有子目录和文件。如果ls [选项] [文件]就只是把这个文件的信息显示给你，这个取决于你的选项。

**常用选项：**

- `-a` 列出目录下的所有文件，包括以 . 开头的隐含文件。
- `-d` 将目录**像文件一样显示**，而**不是显示其下的文件**。 如：`ls –d` 指定目录。这条挺有用的，如果你想看这个目录的权限或者其他信息的时候就用这个选项。
- `-i` 输出文件的 `i` 节点的索引信息。 如 `ls –ai` 指定文件。这个主要是显示文件的`inode`编号，每个文件都会自己的属性信息，就放在这个编号的文件里面，这个我后面应该会总结。
- `-l` 列出文件的详细信息。这条命令`ls -l`可以用`ll`代替。

### 2. pwd

**语法：**`pwd`

**功能：**显示出当前路径。

> 该命令没有选项。

### 3. cd

**语法：**`cd` [目录]

**功能：**改变当前的所在目录。

> 这里说**两个特殊的目录**。`.`和`..`,前者表示当前目录，后者表示上一层目录。
>
> 只输入`cd`表示进入到家目录。
>
> `cd -`表示进入到最近一次访问的目录。（就是上次的那个目录。）

这里还有两个知识点：

**绝对路径：**就是从根目录开始，一层一层列举的目录。例如：`/home/gerald/code`第一个`/`表示根目录，其他的都是目录分隔。

**相对路径：**就是从当前目录开始的目录列举。例如：`../practice/`

### 4.touch

**语法：**`touch` [选项] 文件名..

**功能：**`touch`命令参数可更改文档或目录的日期时间，包括存取时间和更改时间，或者新建一个不存在的文件。主要都是为了新建一个普通文件。

**常用选项：**

> 我到目前为止，没有用过`touch`的选项。一直都是`touch`直接加文件名，创建一个普通文件。

- `-a`   或`--time=atime`或`--time=access`或`--time=use`只更改存取时间。
- `-c`   或`--no-create` 不建立任何文档。
- `-d`  使用指定的日期时间，而非现在的时间。
- `-f`  此参数将忽略不予处理，仅负责解决`BSD`版本`touch`指令的兼容性问题。
- `-m`   或`--time=mtime`或`--time=modify` 只更改变动时间。
- `-r`  把指定文档或目录的日期时间，统统设成和参考文档或目录的日期时间相同。
- `-t`  使用指定的日期时间，而非现在的时间

### 5.mkdir

**语法：**`mkdir` [选项] 目录名..

**功能：**在当前目录下创建一个或多个目录。

**常用选项：**

- `-p`此时若路径中的某些目录尚不存在,加上此选项后,系统将自动建立好那些尚不存在的目录,即一次可以建立多个目录。就是一次创建了多层的目录。

### 6.rm

**语法：**`rm` [选项] [目录名或文件名]..

**功能：**删除目录或文件。

**常用选项：**

- `-f` 即使文件属性为只读(即写保护)，亦直接删除。
- `-i `删除前逐一询问确认。
- `-r` 删除目录及其下所有文件。

所以在root用户下，`rm -rf /`是非常恐怖的事情，直接从删库到跑路了。

### 7.man

**语法：**`man` [选项] 命令

**功能：**这是一个联机手册，所以也有一个说法是有不懂的就去问那个男人。

**常用选项：**

- `num`(1 ~ 8)这个命令最常用的就是这个1~8的数字，每个数字代表不同的章节。

  1 是普通的命令
  2 是系统调用,如`open,write`之类的(通过这个，至少可以很方便的查到调用这个函数，需要加什么头文件) 
  3 是库函数,如`printf,fread4`是特殊文件,也就是/dev下的各种设备文件
  5 是指文件的格式,比如`passwd`, 就会说明这个文件中各个字段的含义
  6 是给游戏留的,由各个游戏自己定义
  7 是附件还有一些变量,比如向`environ`这种全局变量在这里就有说明
  8 是系统管理用的命令,这些命令只能由`root`使用,如`ifconfig`

  **其实最常用的还是前三章。**

### 8.cp

> 这就是我们windows的复制功能。

**语法：**`cp` [选项] 源文件或目录 目标文件或目录
**功能：**复制文件或目录。
**说明：**`cp`指令用于复制文件或目录，如同时指定两个以上的文件或目录，且最后的目的地是一个已经存在的目录，则它会把前面指定的所有文件或目录复制到此目录中。若同时指定多个文件或目录，而最后的目的地并非一个已存在的目录，则会出现错误信息。
**常用选项：**

- `-f` 或 `--force` 强行复制文件或目录， 不论目的文件或目录是否已经存在
- `-i` 或 `--interactive` 覆盖文件之前先询问用户
- `-r` 递归处理，将指定目录下的文件与子目录一并处理。若源文件或目录的形态，不属于目录或符号链接，则一律视为普通文件处理
- `-R` 或 `--recursive`递归处理，将指定目录下的文件及子目录一并处理

### 9.mv

> 有了复制就得有剪贴，当然也可以用来做重命名。

**语法:** `mv` [选项] 源文件或目录 目标文件或目录
**功能:** 

1. 视`mv`命令中第二个参数类型的不同（是目标文件还是目标目录），`mv`命令将文件重命名或将其移至一个新的目录中。
2. 当第二个参数类型是不存在的名字时，`mv`命令完成文件重命名，此时，源文件只能有一个（也可以是源目录名），它将所给的源文件或目录重命名为给定的目标文件名。
3. 当第二个参数是已存在的目录名称时，源文件或目录参数可以有多个，`mv`命令将各参数指定的源文件均移至目标目录中。

**常用选项：**

- `-f ：force` 强制的意思，如果目标文件已经存在，不会询问而直接覆盖
- `-i` ：若目标文件 (destination) 已经存在时，就会询问是否覆盖

### 10.cat

**语法：**cat [选项] [文件] 
**功能：** 查看目标文件的内容。这个命令还是挺常用的吧，经常来看一个文件里面都写了什么。
**常用选项：**

- -b 对非空输出行编号
- -n 对输出的所有行编号
- -s 不输出多行空行

### 11.less

> - less 工具也是对文件或其它输出进行分页显示的工具，应该说是linux正统查看文件内容的工具，功能极其强大。
> - less 的用法比起 more 更加的有弹性。在 more 的时候，我们并没有办法向前面翻， 只能往后面看
> - 但若使用了 less 时，就可以使用 [pageup] [pagedown] 等按键的功能来往前往后翻看文件，更容易用
>   来查看一个文件的内容！
> - 除此之外，在 less 里头可以拥有更多的搜索功能，不止可以向下搜，也可以向上搜

> less打开大文件的效率很高，尤其是几个G的文件时。
>
> less打开文件的时候只是加载一小部分数据加载到内存上，这叫做延迟加载或懒加载。
>
> 但是其他的编辑器都是把整个文件全部加载，这样效率就很低了。

**语法：** `less` [参数] 文件
**功能：**`less`与`more`类似，但使用`less`可以随意浏览文件，而`more`仅能向前移动，却不能向后移动，而且`less`在查看之前不会加载整个文件。

> 因为`more`不如`less`，所以这里就不介绍`more`了，主要是推荐用`less`。

**常用选项**：

- `-i ` 忽略搜索时的大小写。
- `-N`  显示每行的行号。
- `/`字符串：向下搜索“字符串”的功能。
- `?`字符串：向上搜索“字符串”的功能。
- `n`：重复前一个搜索（与 / 或 ? 有关）。
- `N`：反向重复前一个搜索（与 / 或 ? 有关）。
- `q`:quit。

### 12.date

**语法：**`date` [选项] [+格式]

**功能：**主要是显示时间，这个挺常用的，看时间的时候不用切出去看了，直接在全屏状态下输入一条命令就可以啦。

**格式：**如果我们在显示时间的时候想要以某种格式输出，就要下面的选项。（要在这些选项前加`+`号）

- %H : 小时(00..23) 
- %M : 分钟(00..59) 
- %S : 秒(00..61) 
- %X : 相当于 %H:%M:%S 
- %d : 日 (01..31) 
- %m : 月份 (01..12) 
- %Y : 完整年份 (0000..9999) 
- %F : 相当于 %Y-%m-%d

**时间戳：**

时间->时间戳：`date +%s`
时间戳->时间：`date -d@1508749502`
Unix时间戳（英文为Unix epoch, Unix time, POSIX time 或 Unix timestamp）是从1970年1月1日（UTC/GMT的午夜）开始所经过的秒数，不考虑闰秒。

### 13.find

**语法：**`find [选项] [文件名]`

**功能：**用来查找文件在那个路径下。就是你不知道文件在哪了，就找找文件在哪存着。

> Linux下find命令在目录结构中搜索文件，并执行指定的操作。
> Linux下find命令提供了相当多的查找条件，功能很强大。由于find具有强大的功能，所以它的选项也很多，其中大部分选项都值得我们花时间来了解一下。
> 即使系统中含有网络文件系统( NFS)，find命令在该文件系统中同样有效，只你具有相应的权限。
> 在运行一个非常消耗资源的find命令时，很多人都倾向于把它放在后台执行，因为遍历一个大的文件系统可能会花费很长的时间(这里是指30G字节以上的文件系统)。

**常用选项：**

- -name 按照文件名查找文件

### 14.zip/unzip

**语法：**`zip` [目标压缩文件名] [目录或文件]

**功能：**将会目录或文件压缩成zip格式。

**常用选项：**

- -r 递归压缩。就是把一个目录下的所有子目录和文件都压缩。