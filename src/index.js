exports.debugLog = msg => console.log(`[debug] ${msg}`);

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