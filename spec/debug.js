const parser = require("../lib/deps_parser");

const str = { str: "test" };
parser.parser(str).then((val) => {
  console.log(val);
});

console.log('Bang!');
