const pid = require('./pid');
exports.pid = pid;



// ---- basic logs ------------

exports.debugLog = msg => console.log(`[debug] ${msg}`);


// ---- ELK duration logs ------------

const durationLog = durationType => event => {
  const initStr = 'Lambda Event ';
  const durationStr = durationType === 'start' ? 'Start' : 'End';
  const eventStr = JSON.stringify(event);
  const logStr = `${initStr}${durationStr}: ${eventStr}`;
  console.log(logStr);
};
exports.durationLog = durationLog;

exports.startLog = event => durationLog('start')(event);
exports.endLog = event => durationLog('end')(event);


// --- ELK action logs ------------

const STAGE = process.env.STAGE || 'UNKNOWN_ENV';

const actionLog = actionType => logLevel => payload => {
  const initStr = `${STAGE},${logLevel},${actionType},`;

  const {group, method, data = '', memberId = null } = payload;
  const rawData = typeof data === 'object' ? JSON.stringify(data) : data;
  const memberIdStr = memberId == null ? '' : `${memberId},`;
  const payloadStr = `${group},${method},${memberIdStr}${rawData}`;

  const logStr = `${initStr}${payloadStr}`;
  console.log(logStr);
};
exports.actionLog = actionLog;

const handlerLog = logLevel => payload => actionLog('handler')(logLevel)(payload);
exports.handlerLog = handlerLog;

exports.handlerLogDebug = payload => handlerLog('debug')(payload);
exports.handlerLogInfo = payload => handlerLog('info')(payload);
exports.handlerLogWarning = payload => handlerLog('warning')(payload);
exports.handlerLogError = payload => handlerLog('error')(payload);

const modelLog = logLevel => payload => actionLog('model')(logLevel)(payload);
exports.modelLog = modelLog;

exports.modelLogDebug = payload => modelLog('debug')(payload);
exports.modelLogInfo = payload => modelLog('info')(payload);
exports.modelLogWarning = payload => modelLog('warning')(payload);
exports.modelLogError = payload => modelLog('error')(payload);


// --- ELK action log payload wrapping ------------

// payload = getLogPayload(FUNC_NAME)('xxxmethod')(data)(int|null);
exports.getLogPayload = groupName => methodName => data => (memberId = null) => ({
  group: groupName,
  method: methodName,
  data,
  memberId
});