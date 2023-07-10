const parser = require("../lib/deps_parser");

parser.parser("test").then((val) => {
  console.log(val);
});
