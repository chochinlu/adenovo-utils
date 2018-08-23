# Adenovo utils

Util methods for [Adenovo](https://www.adenovo.com/).

## Usage

#### Basic log:

``` js
const {debugLog} = require('adenovo-utils');

debugLog('for debug usage');  // [debug] for debug usage
```

#### For ELK duration logs:

``` js
const {durationLog, startLog, endLog} = require('adenovo-utils');

const event = {foo: 'bar', hello: 'world'}; // your event object

durationLog('test')(event); // Lambda Event End: {"foo":"bar","hello":"world"}

startLog(event); // Lambda Event Start: {"foo":"bar","hello":"world"}

endLog(event); // Lambda Event End: {"foo":"bar","hello":"world"}
```

#### For ELK action logs (basic):

``` js
const {actionLog} = require('adenovo-utils');

const event = {foo: 'bar', hello: 'world'};
const payload = {group: 'mygroup', method: 'paySomething', data: event}; // optional: memberId

actionLog('handler')('debug')(payload); // DEV,debug,handler,mygroup,paySomething,{"foo":"bar","hello":"world"}

```

#### For ELK action logs (more specific):

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

``` js
const {handlerLog, modelLog, handlerLogDebug, modelLogWarning} = require('adenovo-utils');

const event = {foo: 'bar'};
const payload = {group: 'mygroup', method: 'paySomething', data: event};

handlerLog('hello')(payload); // DEV,hello,handler,mygroup,paySomething,{"foo":"bar"}
modelLog('world')(payload); // DEV,world,model,mygroup,paySomething,{"foo":"bar"}
handlerLogDebug(payload); // DEV,debug,handler,mygroup,paySomething,{"foo":"bar"}
modelLogWarning(payload); // DEV,warning,model,mygroup,paySomething,{"foo":"bar"}
```

#### ELK action log payload wrapping:

``` js
const {handlerLogInfo, getLogPayload} = require('adenovo-utils');

const FUNC_TITLE = 'xxxxPayment';
const logFuncPayload = getLogPayload(FUNC_TITLE);

// ...

const methodName = 'xxxPaymentCallback';
const logPayload = logFuncPayload(methodName);

// ...

const orderInfo = {foo: 'bar'};
const member_id = 1234;
handlerLogInfo(logPayload(orderInfo)(memberId));
```