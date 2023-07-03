/** @type {import('ts-jest').JestConfigWithTsJest} */
module.exports = {
  preset: 'ts-jest',
  coverageProvider: 'v8',
  coverageThreshold: {
    global: {
      branches: 96,
      functions: 61,
      lines: 66,
      statements: 66,
    },
  },
};
