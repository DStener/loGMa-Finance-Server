# API - Auth service
### `POST /api/auth/login`
> Авторизация пользователя
- Input: 
  ```js
  JSON_OBJECT:
  {
    "login": string,
    // Password in MD5
    "password": string
  }
  ```
- Output:
  - Success
    ```js
    STATUS_CODE: 200
    ```
  - Error
    ```js
    STATUS_CODE: 416
    JSON_OBJECT:
    {
      "message": string
    }
    ```

### `POST /api/auth/register`
> Регистрация нового пользователя 
- Input: 
  ```js
  JSON_OBJECT:
  {
    "login": string,
    "name": string,
    "surname": string,
    "patronymic": string,
    "birthday": timestamp,
    // Password in MD5
    "password": string,
  }
  ```
- Output:
  - Success
    ```js
    STATUS_CODE: 201
    ```
  - Error
    ```js
    STATUS_CODE: 416
    JSON_OBJECT:
    {
      "message": string
    }
    ```

### `GET /api/auth/me`
> Получение инофрмации о себе  
- Input: 
  ```js
  NONE
  ```
- Output:
  - Success
    ```js
    STATUS_CODE: 200
    JSON_OBJECT:
    {
      // id in DB
      "id": integer,
      // id of avatar file 
      "avatar": integer,
      "name": string,
      "surname": string,
      "patronymic": string,
      "birthday": timstamp,
    }
    ```
  - Error
    ```js
    STATUS_CODE: 403
    JSON_OBJECT:
    {
      "message": string
    }
    ```

### `POST /api/auth/out`
  > Выход из текущей сессии 
- Input: 
  ```js
  NONE
  ```
- Output:
  - Success
    ```js
    STATUS_CODE: 200
    ```
  - Error
    ```js
    STATUS_CODE: 403
    JSON_OBJECT:
    {
      "message": string
    }
    ```

### `POST /api/auth/out/{id_session}`
  > Выход из сесси с индексом `id_session`
- Input: 
  ```js
  NONE
  ```
- Output:
  - Success
    ```js
    STATUS_CODE: 200
    ```
  - Error
    ```js
    STATUS_CODE: 403
    JSON_OBJECT:
    {
      "message": string
    }
    ```
### `POST /api/auth/out_all`
  > Выход из всех сессий 
- Input: 
  ```js
  NONE
  ```
- Output:
  - Success
    ```js
    STATUS_CODE: 200
    ```
  - Error
    ```js
    STATUS_CODE: 403
    JSON_OBJECT:
    {
      "message": string
    }

### `POST /api/auth/session`
  > Список всех активных сессий пользователя
- Input: 
  ```js
  NONE
  ```
- Output:
  - Success
    ```js
    STATUS_CODE: 200
    JSON_OBJECT:
    [
      0: {
        "id": integer,
        // icon is id of File in DB
        "icon": integer,
        "session_name": string,
        "time": timestamp,
        "is_current": bool
      } 
      ...
    ]
    ```
  - Error
    ```js
    STATUS_CODE: 403
    JSON_OBJECT:
    {
      "message": string
    }

