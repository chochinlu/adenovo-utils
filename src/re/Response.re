type responseResult =
  | Ok
  | Created
  | BadRequest((string, Js.Json.t))
  | Unauthorized((string, Js.Json.t))
  | InternalServerError((string, Js.Json.t));

let code = (resp: responseResult) : int =>
  switch resp {
  | Ok => 200
  | Created => 201
  | BadRequest(_) => 400
  | Unauthorized(_) => 401
  | InternalServerError(_) => 500
  };

let getBody =  (resp: responseResult): Js.Json.t => switch resp {
  | Ok
  | Created => Js.Json.null
  | BadRequest((_, body)) 
  | Unauthorized((_, body))
  | InternalServerError((_, body)) => body
};

let formatedLog = (msg, title, body: Js.Json.t) => title ++ ": " ++ msg ++ ". body: " ++ Js.Json.stringify(body);

let msg = (resp: responseResult) : string =>
  switch (resp) {
  | Ok => "Ok"
  | Created => "Created"
  | BadRequest((title, body)) => "Missing or Bad Parameters" -> formatedLog(title, body)
  | Unauthorized((title, body)) => "User Authentication Error" -> formatedLog(title, body)
  | InternalServerError((title, body)) => "Internal Server Error" -> formatedLog(title, body)
  };

let saveMsg =  (resp: responseResult)  => {
  resp -> msg -> Js.log;
  resp;
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

let resp = (result: responseResult) => 
  responseObj(
    ~statusCode=code(result),
    ~headers=basicHeader,
    ~body=result -> getBody -> Js.Json.stringify,
  );

let respOk =  () => Ok -> resp;
let respCreated = () => Created -> resp;
let respBadRequest = (title, body) => BadRequest((title, body)) -> saveMsg -> resp;
let respUnAuthed = (title, body) => Unauthorized((title, body)) -> saveMsg -> resp;
let respServerErr = (title, body) => InternalServerError((title, body)) -> saveMsg -> resp;

