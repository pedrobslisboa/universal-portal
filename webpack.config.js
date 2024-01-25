const Path = require("path");

let buildFolder = Path.join(__dirname, "_build/default/demo");

module.exports = (env) => ({
  devtool: env.production ? false : "inline-cheap-module-source-map",
  entry: {
    app: Path.join(buildFolder, "/client/app/demo/client/app.js"),
  },
  mode: env.production ? "production" : "development",
  output: {
    path: Path.join(__dirname, "static"),
    filename: "[name].js",
  },
  resolve: {
    alias: {
      "@emotion/hash": Path.join(buildFolder, "hash", "client", "hash.js"),
    },
  },
});
