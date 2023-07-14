const parser = require("../lib/deps_parser");

const str = String("test");
parser.parser(str, {}).then((val) => {
  console.log(val);
});
