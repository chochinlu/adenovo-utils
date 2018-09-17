# Adenovo utils

Util methods for [Adenovo](https://www.adenovo.com/), maybe you can find what utils you want here.

- [Pid](#pid)
- [Basic log](#basic-log)
- [Functional utils](#functional-utils): pipe, pipeAsync, compose, composeAsync...
- [Object utils](#object-utils): check if object empty, remove empty values from object...

## Usage

### Pid

中華民國身分證字號檢查與產生器, 基於[wiki](https://zh.wikipedia.org/wiki/%E4%B8%AD%E8%8F%AF%E6%B0%91%E5%9C%8B%E5%9C%8B%E6%B0%91%E8%BA%AB%E5%88%86%E8%AD%89#%E7%B7%A8%E8%99%9F%E8%A6%8F%E5%89%87)

```js
const { checkPid, genPid } = require("adenovo-utils").pid;

const somePid = genPid(); //'B169298328'
const errorResult = checkPid("dsds"); // { result: false, msg: '身分證字號長度不正確' }

const okResult = checkPid("B169298328"); // { result: true }
```

### Basic log

```js
const { debugLog } = require("adenovo-utils").log;

debugLog("for debug usage"); // [debug] for debug usage
```

### For ELK duration logs:

```js
const { durationLog, startLog, endLog } = require("adenovo-utils").log;

const event = { foo: "bar", hello: "world" }; // your event object

durationLog("test")(event); // Lambda Event End: {"foo":"bar","hello":"world"}

startLog(event); // Lambda Event Start: {"foo":"bar","hello":"world"}

endLog(event); // Lambda Event End: {"foo":"bar","hello":"world"}
```

### For ELK action logs (basic)

```js
const { actionLog } = require("adenovo-utils").log;

const event = { foo: "bar", hello: "world" };
const payload = { group: "mygroup", method: "paySomething", data: event }; // optional: memberId

actionLog("handler")("debug")(payload); // DEV,debug,handler,mygroup,paySomething,{"foo":"bar","hello":"world"}
```

### For ELK action logs (more specific)

Includes:

- handlerLog(logLevel: string)(payload: object)
- handlerLogDebug(payload)
- handlerLogInfo
- handlerLogWarning
- handlerLogError
- modelLog(logLevel: string)(payload: object)
- modelLogDebug(payload)
- modelLogInfo
- modelLogWarning
- modelLogError

For example:

```js
const {
  handlerLog,
  modelLog,
  handlerLogDebug,
  modelLogWarning
} = require("adenovo-utils").log;

const event = { foo: "bar" };
const payload = { group: "mygroup", method: "paySomething", data: event };

handlerLog("hello")(payload); // DEV,hello,handler,mygroup,paySomething,{"foo":"bar"}
modelLog("world")(payload); // DEV,world,model,mygroup,paySomething,{"foo":"bar"}
handlerLogDebug(payload); // DEV,debug,handler,mygroup,paySomething,{"foo":"bar"}
modelLogWarning(payload); // DEV,warning,model,mygroup,paySomething,{"foo":"bar"}
```

### ELK action log payload wrapping

```js
const { handlerLogInfo, getLogPayload } = require("adenovo-utils").log;

const FUNC_TITLE = "xxxxPayment";
const logFuncPayload = getLogPayload(FUNC_TITLE);

// ...

const methodName = "xxxPaymentCallback";
const logPayload = logFuncPayload(methodName);

// ...

const orderInfo = { foo: "bar" };
const member_id = 1234;
handlerLogInfo(logPayload(orderInfo)(memberId));
```

### Functional utils

```js
const {
  pipe,
  pipeAsync,
  compose,
  composeAsync
} = require("adenovo-utils").functional;

const fn1 = a => a + 2;
const fn2 = a => a * 3;

const resp1 = pipe(
  fn1,
  fn2
)(3); //  3 -> fn1 -> fn2 , result: 15

const resp2 = compose(
  fn1,
  fn2
)(3); // 3 -> fn2 -> fn1, result: 11
```

`pipeAsync` and `composeAsync` are async pipe/compose version, you can chain your async functions !

### Object utils

`removeEmpty` will remove the null and undefined entries from an object (will not remove empty string value).

```js
const { isEmpty, removeEmpty } = require("adenovo-utils").obj;

const obj1 = {};
const obj2 = { a: 1, b: 2 };

const result1 = isEmpty(obj1); // true
const result2 = isEmpty(obj2); // false

const obj3 = { a: 1, b: undefined, c: null, d: 1, e: "" };
const result3 = removeEmpty(a); // { a: 1, d: 1, e: '' }
```

a `{key: key}` translator:

```js
const { keyMirror } = require("adenovo-utils").obj;

const arr1 = ["a", "b"];
keyMirror(arr1); //{ a: 'a', b: 'b'}

const arr2 = [1, 2];
keyMirror(arr2); //{ '1': 1, '2': 1}
```

### Serverless Response Wrapper

Included methods:

- resp
- respOk
- respCreated
- respBadRequest
- respUnAuthed
- respServerErr

```js
const { respBadRequest } = require("adenovo-utils").res;
respBadRequest("hello", { foo: "bar" }); // console.log ->  hello: Missing or Bad Parameters. body: {"foo":"bar"}
```

For example, the `respBadRequest` method will response the following object:

```json
{
  "statusCode": 400,
  "headers": {
    "Access-Control-Allow-Origin": "*",
    "Access-Control-Allow-Credentials": true
  },
  "body": "{\"foo\":\"bar\"}"
}
```

## Development

### ReasonML

Fisrt git clone this repo, then:

```txt
$ npm run bsstart // run bucklescript watch server
$ npm run bsbuild
$ npm run baclean // clear all *.bs.js
```
