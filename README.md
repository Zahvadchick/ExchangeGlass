В данном решении предложено 3 варианта реализации биржевого стакана: 

__Первый__ заключается в хранении заявок в отсортированных двусвязных списках (list), то есть при добавлении и изменении заявки мы учитываем позицию в зависимости от стоимости.

__Второй__ хранит данные в множествах (set), то есть также как и в первом случае данные упорядоченны, только в первом случае порядок соблюдаем благодаря моей реализации, а во втором посредством хранения данных в сбалансированном BTS.

__Третий__ вариант, в отличии от предыдущих двух, хранит данные в неупорядоченном порядке, но перед каждым вызовом отображения лучших заявок мы вызываем сортировку. Для хранения используются обыкновенные динамические массивы (vector).

### Особенности
Структура заявки состоит не только из параметров, заданных в ТЗ (стоимость, количество и тип операции), но и их уникалького индификатора. Сделано это для того, чтобы при методе изменения мы могли найти старый вид заявки, а также для более котороткого отчета в тестовой системе (в случае падения теста перечисляются id выведенных заявок, а также id которые должны были быть выведены).

У каждого варианта есть несколько особенностей, которые общие для них всех. Первая такая особенность заключается в том, что мы храним заявки на продажу и на покупку в разных контейнерах. Во время отображения заявок выдаются по 10 (конструктор позволяет задать другое число, количество 10 взято с ТЗ) с каждого из них для того, чтобы видить на сколько близки спрос и предложение. Вторая особенность это хэшированный словарь (unordered_map), который я использовал для того, чтобы быстро (скорость армотизированная O(1)) находить есть ли заявка с данным id (ключ мапы). Кроме этого я в значениии мапы храню саму заявку для того, чтобы знать старый вид заявки при вызове метода изменения (для того чтобы удалить ее при необходимости и добавить новую). Третья особенность - метод Sell, который в случае пересечения по цене заявок продажи и покупки осуществляет сделку, то есть удаляет лучшие заявки из каждого контейнера до тех пор, пока пересечение не будет устраненно.

### Методы
Добавление
За добавление заявка отвечает метод Add. В качестве аргумента он принимает ссылку на заявку которую нужно добавить. В первом варианте реализации мы находим итератор с помощью функции upper_bound (сложность операции линейная, так как лист поддерживает только инкремент и декремент), затем по итератору вставляем заявку (сложно константная, так как вставляем по итератору), в итоге имеем линейную сложность выполнения. Во втором варианте мы просто делаем insert в set, из-за особенностей set мы имеем логарифмическую временную сложность. В третьем варианте мы делаем push_back (добавляем в конец) сложность операции армотизированная константа.

Изменение
Для изменения заявки используется метод Change, который принимает в качестве аргумента новый вид заявки. Старый вид, который нужно заменить находится по совпадающему id. В первом варианте мы проверяем, одинакова ли стоимость, и если она одинакова, то мы находим итератор старой заявки и перезаписываем в него значение новой. Если стоимость различна, то мы удаляем старую и добавляем новую. Такой подход обусловлен тем, что в случае одинаковой цены новая заявка будет находится на месте старой, и тогда мы можем сделать одну операцию с линейной сложностью (поиск итератора) вместо двух (удаления и добавление). Во втором и третьем варианте реализации мы всего удаляем старую и добавляем новую. Во втором варианте сложности удаления и добавления логарифмические, кроме того итераторы у set всегда константные. В третьем варианте сложность добавления армотизированная константа, следовательно добавление кейса с одинаковой стоимостью только усложнит код.

Удаление
Удаление переданной заявки осуществляется с помощью метода Erase. В первом и третьем варианте мы находим итератор заявки и удаляем по нему. В первом варианте поиск занимает линейное время, а удаление константное, а в третьем и поиск и удаление будут линейными, сумарно в обоих случаях сложность линейная. Во втором случае мы просто вызываем стандартное удаление из set, которое имеет логарифмическую сложность.

Вывод лучших заявок
За вывод лучших заявок продажи и покупки отвечает метод BestApplications. Первая половина выданных заявок будет на продажу, в порядке невозрастания, вторая половина - заявки на покупку в томже порядке. Таким образом в середине будут самая дешевая заявка на продажу и самая дорогая на покупку, то есть лучшие с каждой стороны. Таким образом я подошел как можно ближе к реалиным биржевым стаканам, где сверху вниз идут заявки на продажу в порядке уменьшения цены, в середине идет спред, а потом сверху вниз продажа от самой дорогой к самой дешевой. Во всех трех версиях я просто итерируюсь с конца или начала отсортированных контейнеров и передаю значение итератора в выходной вектор. Важное замечание - перед итерацией в третьей версии я использую быструю сортировку, так как вектора первоначально не отсортированны. Сложность такой сортировки в худшем случае O(n^2), но он крайне редок, обычно сложность O(n * log(n)).

Продажа
Метода Sell, как я говорил раньше, осуществляет сделки между покупателями и продавцами, если они возможны. Данный метод в первой реализации вызывается после каждого добавления заявки, во втором и третьем перед выводом лучших заявок. Возможно лучше всего сделать его вызов независимым и совершать его переодически, как например метод BestApplications, но чаще. Реализация такова, что программа проверяет цену лучшей заявки продажи и покупки. Сделка совершается до тех пор, пока цена продажи не превышает цену покупки. В случае сделки мы проверяем количество лучших заявок покупки и продажи, если оно одинаково, то удаляются обе заявки, если одной из них больше, то она теряет количество равное количеству заявки противоположного типа, заявка противоположного типа удаляется.

### Таблица сложностей операций

__Первая версия__
Метод | Сложность
:-----|:---------:
Add | O(n)
Change | O(n)
Erase | O(n)
BestApplications | O(1)

__Вторая версия__
Метод | Сложность
:-----|:---------:
Add | O(log(n))
Change | O(log(n))
Erase | O(log(n))
BestApplications | O(n * log(n))

Важное замечание: сложность самого BestApplications O(1), но во второй реализации также срабатывает метод Sell, который тратит на одну сделку O(log(n)) времени, а таких сделок за раз может быть n.

__Третьея версия__
Метод | Сложность
:-----|:---------:
Add | O(1)
Change | O(n)
Erase | O(n)
BestApplications | O(n^2)

И по асимптотической оценке и по замерам времени выполнения тестов второй вариант является фаворитом. Между первым и третьим чаще всего первый является фаворитом, но при малом количестве заявок или/и редком вызове BestApplications третий может с ним побороться.

### Тестирование

Было написано 4 теста: 
__SimpleTest__ проверяет работу методов из ТЗ, то есть добавление, изменение и удаление заявки, а также отображение лучших. Мы добавляем несколько заявок, затем удаляем по одной каждого типа, изменяем одну заявку так, чтобы она поменяла позицию в списке лучших, после чего изменяем тип заявки. После каждого действия проверяем список лучших заявок на корректность.

__SellTest__ проверяет продажу заявок. Первоначально мы добавляем несколько заявок, после чего еще одну на покупку, из-за которой одна заявка из продаж удаляется, а у другой снижается объём. Затем добавляем заявку на продажу, из-за которой удаляется две заявки из покупок. Также проверяем корректность данных после каждого действия.

__ManyApplicationsTest__ создает по 10 заявок на покупку и продажу в следствии чего наслаждаемся полностью забитым стаканом, а потом наблюдаем как после добавления еще трех различных заявки, из-за чего часть заявок уходят из списка лучших, а часть других сдвигается по приоритету. Затем удаляем 3 заявки и наблюдаем как в список лучших возвращаются ушедшие заявки.

__SpeedTest__ данный тест не проверяет на корректность выполняемые действия, он просто вызывает каждый метод большое количество раз для того, чтобы программа не завершалась мгновенно и мы могли увидеть разницу в быстродействии каждой реализации на практике

### Как можно улучшить / от чего отказался

1. Для того чтобы это стало полноценным приложением нужно обернуться все в api для вызовов извне, подключить СУБД, добавить логеры и тд
2. Здесь могло быть больше версий реализации, но как мне показалось это излишне, так как принципиально они не будут отличаться от текущих. Например сделать анлогично первому только с вектором, тогда например поиск элемента был бы O(log(n)) вместо O(n), так как вектор поддерживает RandomAccessIterator, а следовательно мы могли бы искать бинарным поиском, сам факт вставки был бы за O(n), вместо O(1), так как вектору нужно перестраиваться, в то время как в списке просто переназначаются ссылки на предыдущий и следующий элемент, но суммарно это был бы тот же O(n) в итоге.
3. Запуск разных тестов асинхронно, но тогда отчет о тестировании не мог бы быть общим из-за неявного порядка завершения, следовательно нужно было бы логгировать каждый отчет отдельно в файл или еще куда, что мне показалось излишним для задания, так как это сложнее проверять. P.S. только сейчас подумал о том, чтобы логировать их просто в строковые потоки ввода, а потом из них выводить в общий консольный.
