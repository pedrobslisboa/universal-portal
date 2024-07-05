let globalStyles = {js|
  html, body, #root {
    display: flex;
    margin: 0;
    padding: 0;
  }

  * {
    font-family: -apple-system, BlinkMacSystemFont, Roboto, Helvetica, Arial, sans-serif;
    -webkit-font-smoothing: antialiased;
    -moz-osx-font-smoothing: grayscale;
    box-sizing: border-box;
  }

  @keyframes spin {
    to {
      transform: rotate(360deg);
    }
  }
|js};

module Page = {
  [@react.component]
  let make = (~children, ~scripts=[]) => {
    <html>
      <head>
        <meta charSet="UTF-8" />
        <meta
          name="viewport"
          content="width=device-width, initial-scale=1.0"
        />
        <title> {React.string("Server Reason React demo")} </title>
        <link
          rel="shortcut icon"
          href="https://reasonml.github.io/img/icon_50.png"
        />
        <style
          type_="text/css"
          dangerouslySetInnerHTML={"__html": globalStyles}
        />
      </head>
      <body>
        <div id="root"> children </div>
        {scripts |> List.map(src => <script defer=true src />) |> React.list}
      </body>
    </html>;
  };
};

let handler =
  Dream.router([
    Dream.get("/", _request => {
      let portals: ref(array(UniversalPortal_Shared.Portal.portal)) =
        ref([||]);

      let element =
        ReactDOM.renderToString(
          UniversalPortal_Server.collectPortals(
            <Page scripts=["/static/app.js"]>
              <Shared_native_demo.App />
            </Page>,
            (collectedPortal: UniversalPortal_Shared.Portal.portal) => {
            portals := Array.append(portals^, [|collectedPortal|])
          }),
        );

      let html =
        UniversalPortal_Server.appendUniversalPortals(element, portals^);

      portals := [||];

      html |> Dream.html;
    }),
    Dream.get("/static/**", Dream.static("./static")),
  ]);

let interface =
  switch (Sys.getenv_opt("SERVER_INTERFACE")) {
  | Some(env) => env
  | None => "localhost"
  };

Dream.run(~port=8080, ~interface, handler);
