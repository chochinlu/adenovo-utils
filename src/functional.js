const _pipe = (f, g) => (...args) => g(f(...args))

const pipe = (...fns) => fns.reduce(_pipe);

const pipeAsync = (...fns) => input => fns.reduce((chain, func) => chain.then(func), Promise.resolve(input));

const compose = (...fns) => fns.reduce((f, g) => (...args) => f(g(...args)));

const composeAsync = (...fns) => input => fns.reduceRight((chain, func) => chain.then(func), Promise.resolve(input));

const printLog = source => {
  console.log({source});
  return source;
};

exports.pipe = pipe;
exports.pipeAsync = pipeAsync;
exports.compose = compose;
exports.composeAsync = composeAsync;
exports.printLog = printLog;