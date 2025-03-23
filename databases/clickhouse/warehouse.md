Мы хотим получить только `product_id`, которые были обновлены сегодня, с остатками на складе где data вчерашняя.

```sql
SELECT        product_id
FROM          products final
INNER JOIN    remainders final using(product_id)
WHERE         updated = Today() AND date = Today()-1
```

1 - порядок фильтрации & объединения - в начале фильтруем данные, затем объединяем
2 - здесь inner join (работает со всеми значениями из строк) создает таблицу из значений products и remainders (разные таблицы) используя product_id
3 - FINAL добавляет накладные расходы на операции, но дедуплицирует записи. replacingMergeTree удаляет дубликаты (не не гарантирует, что их не будет). Можно удалить, если дубликаты допускаются.

```sql
SELECT product_id
FROM products [FINAL]
WHERE
  udpated = Today() AND
  product_id IN (
    SELECT product_id
    FROM remainders [FINAL]
    WHERE date = Today()-1
  )
```

> расчитываем, что ReplacingMergeTree удалит дубликаты, но держим в уме, что на это гарантий нету. Здесь FINAL дедуплицирует данные.
> можно использовать другие оптимизации из доки. Например, поменять местами порядок таблиц.
