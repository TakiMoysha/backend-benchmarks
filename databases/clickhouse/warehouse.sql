CREATE TABLE products (
  product_id Int32,
  product_name String,
  brand_id Int32,
  seller_id Int32,
  updated Date
) ENGINE = ReplacingMergeTree ORDER BY product_id

CREATE TABLE remainders (
  date Date,
  product_id Int32,
  remainder Int32,
  price Int32,
  discount Int32,
  pics Int32,
  rating Int32,
  reviews Int32,
  new Bool
) ENGINE = ReplacingMergeTree ORDER BY (date, product_id)


