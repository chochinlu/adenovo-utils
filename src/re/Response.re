type statusCode =
  | Ok
  | Created
  | BadRequest
  | Unauthorized
  | InternalServerError;

let code = (someCode: statusCode) : int =>
  switch (someCode) {
  | Ok => 200
  | Created => 201
  | BadRequest => 400
  | Unauthorized => 401
  | InternalServerError => 500
  };

[@bs.deriving abstract]
type headers = {
  [@bs.as "Access-Control-Allow-Origin"]
  allowOrigin: string,
  [@bs.as "Access-Control-Allow-Credentials"]
  allowCredentials: bool,
};

let basicHeader = headers(~allowOrigin="*", ~allowCredentials=true);

[@bs.deriving abstract]
type responseObj = {
  statusCode: int,
  headers,
  body: string,
};

let resp = (someCode: statusCode, body: Js.Json.t) =>
  responseObj(
    ~statusCode=code(someCode),
    ~headers=basicHeader,
    ~body=Js.Json.stringify(body),
  );

let responseOk = Ok -> resp;
let responseAddOk = Created -> resp;
let responseBadRequest = BadRequest -> resp;
let responseNotAuth = Unauthorized -> resp;
let responseInternalErr = InternalServerError -> resp;

let responseErr = responseBadRequest;

let responseErrWithMsg = (msg: string) =>
  {j|{"message": $msg}|j} -> Js.Json.string -> responseBadRequest;

let responseAddOperationOk = {j|{"result": "ok"}|j} -> Js.Json.string -> responseBadRequest;

