/* eslint-disable @typescript-eslint/no-var-requires */
const { basename } = require('path');

const module_name = basename(__filename, '.js');

module.exports = require(`./../build/Debug/${module_name}-${process.arch}`);
