# API

## Auth service

| Method | Path                     | Description | Input | Output |
|:-------|:-------------------------|:-----------:|:-----:|-------:|
| POST   | /api/auth/login          | -           |       |        |
| POST   | /api/auth/register       | -           |       |        |
| GET    | /api/auth/me             | -           |       |        |
| POST   | /api/auth/out            | -           |       |        |
| POST   | /api/auth/out_all        | -           |       |        |
| GET    | /api/auth/tokens         | -           |       |        |

## File service

| Method | Path                      | Description                                     | Input | Output |
|:-------|:--------------------------|:-----------------------------------------------:|:-----:|-------:|
| GET    | /api/ref/file/`{id_file}`        | -                                               |       |        |
| GET    | /api/ref/file/`{id_file}`/avatar | -                                               |       |        |
| POST   | /api/ref/file             | Upload                                          |       |        |
| PUT    | /api/ref/file/`{id_file}`        | Update                                          |       |        |
| DELETE | /api/ref/file/`{id_file}`        | Delete file                                     |       |        |

## Wall service

### Wall

| Method | Path                      | Description                                     | Input | Output |
|:-------|:--------------------------|:-----------------------------------------------:|:-----:|-------:|
| POST   | /api/ref/wall             | Create                                          |       |        |
| PUT    | /api/ref/wall/`{id_wall}`       | Update                                          |       |        |
| GET    | /api/ref/wall/`{id_wall}`        | Get                                             |       |        |
| DELETE | /api/ref/wall/`{id_wall}`        | Delete                                          |       |        |

### Category

| Method | Path                            | Description                                     | Input | Output |
|:-------|:-----------------------------------------------------------|:-----------------------------------------------:|:-----:|-------:|
| GET    | /api/ref/wall/`{id_wall}`/category/                        | Get list                                        |       |        |
| GET    | /api/ref/wall/`{id_wall}`/category/`{id_category}`         | Get                                             |       |        |
| POST   | /api/ref/wall/`{id_wall}`/category                         | Create                                          |       |        |
| PUT    | /api/ref/wall/`{id_wall}`/category/`{id_category}`         | Update                                          |       |        |
| DELETE | /api/ref/wall/`{id_wall}`/category/`{id_category}`         | Delete                                          |       |        |

### Auto rule of Category

| Method | Path                            | Description                                     | Input | Output |
|:-------|:---------------------------------------------------------------------|:-----------------------------------------------:|:-----:|-------:|
| GET    | /api/ref/wall/`{id_wall}`/category/`{id_category}`/role              | Get list                                        |       |        |
| GET    | /api/ref/wall/`{id_wall}`/category/`{id_category}`/role/`{id_role}`  | Get                                             |       |        |
| POST   | /api/ref/wall/`{id_wall}`/category/`{id_category}`/role              | Create                                          |       |        |
| PUT    | /api/ref/wall/`{id_wall}`/category/`{id_category}`/role/`{id_role}`  | Update                                          |       |        |
| DELETE | /api/ref/wall/`{id_wall}`/category/`{id_category}`/role/`{id_role}`  | Delete                                          |       |        |

### Operation

| Method | Path                            | Description                                     | Input | Output |
|:-------|:---------------------------------------------------------------------|:-----------------------------------------------:|:-----:|-------:|
| GET    | /api/ref/wall/`{id_wall}`/operation/                                 | Get list                                        |       |        |
| GET    | /api/ref/wall/`{id_wall}`/operation/`{id_operation}`                 | Get                                             |       |        |
| POST   | /api/ref/wall/`{id_wall}`/operation/                                 | Create                                          |       |        |
| PUT    | /api/ref/wall/`{id_wall}`/operation/`{id_operation}`                 | Update                                          |       |        |
| DELETE | /api/ref/wall/`{id_wall}`/operation/`{id_operation}`                 | Delete                                          |       |        |

### Currenncy 
| Method | Path                            | Description                                     | Input | Output |
|:-------|:---------------------------------------------------------------------|:-----------------------------------------------:|:-----:|-------:|
| GET    | /api/ref/currency                                                    | Get list                                        |       |        |
| GET    | /api/ref/currency/`{id_currency}`                                    | Get                                         |       |        |
