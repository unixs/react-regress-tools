/* eslint-disable @typescript-eslint/no-var-requires */
const { basename } = require('path');

const module_name = basename(__filename, '.js');

const build_type = process.env.NODE_ENV == 'development' ? 'Debug' : 'Release';

module.exports = require(`./${module_name}-${process.arch}-${build_type}`);
