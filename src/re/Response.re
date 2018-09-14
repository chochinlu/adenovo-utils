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

let jsonStr = (body: Js.Json.t) => body -> Js.Json.stringify;
let jsonStrBodyMsg =  (body: Js.Json.t) => ", body: " ++ jsonStr(body);

let msg = ((someCode: statusCode,  body: Js.Json.t)) : string =>
  switch (someCode) {
  | Ok => "Ok"
  | Created => "Created" 
  | BadRequest => "Missing or Bad Parameters" ++ jsonStrBodyMsg(body)
  | Unauthorized => "User Authentication Error" ++ jsonStrBodyMsg(body)
  | InternalServerError => "Internal Server Error" ++ jsonStrBodyMsg(body)
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

let resp = (someCode: statusCode, body: Js.Json.t) => {
  (someCode, body) -> msg -> Js.log;

  responseObj(
    ~statusCode=code(someCode),
    ~headers=basicHeader,
    ~body=body -> jsonStr,
  );
};

let respOk = Ok -> resp;
let respCreated = Created -> resp;
let respBadRequest = BadRequest -> resp;
let respUnAuthed = Unauthorized -> resp;
let respServerErr = InternalServerError -> resp;