// check if obj is empty
const isEmpty = (obj) => {
  for (const key in obj) {
    if (obj.hasOwnProperty(key)) return false;
  }
  return true;
};

// remove null and undefined entries from an object
const removeEmpty = obj =>
  Object.keys(obj)
    .filter(j => obj[j]!==null && obj[j] !== undefined)
    .reduce((a, b) => ({...a, [b]:obj[b]}), {});

exports.isEmpty = isEmpty;
exports.removeEmpty = removeEmpty;