let collectPortal =
  Alcotest.test_case(
    "should collect portals",
    `Quick,
    () => {
      let portals: ref(array(UniversalPortal_Shared.Portal.portal)) =
        ref([||]);

      let _ =
        ReactDOM.renderToString(
          UniversalPortal_Server.collectPortals(
            <body>
              <div>
                <UniversalPortal_Shared.Portal selector="body">
                  <div> {React.string("Hello")} </div>
                </UniversalPortal_Shared.Portal>
                <UniversalPortal_Shared.Portal selector="#portal-root">
                  <div> {React.string("World!")} </div>
                </UniversalPortal_Shared.Portal>
              </div>
              <div id="portal-root" />
            </body>,
            (collectedPortal: UniversalPortal_Shared.Portal.portal) => {
            portals := Array.append(portals^, [|collectedPortal|])
          }),
        );

      Alcotest.(check(int))("portal length", 2, Array.length(portals^));
      Alcotest.(check(string))(
        "portal selector",
        "body",
        portals^[0].selector,
      );
      Alcotest.(check(string))(
        "portal selector",
        "#portal-root",
        portals^[1].selector,
      );
      Alcotest.(check(string))(
        "portal content",
        "<div>Hello</div>",
        ReactDOM.renderToStaticMarkup(portals^[0].content),
      );
      Alcotest.(check(string))(
        "portal content",
        "<div>World!</div>",
        ReactDOM.renderToStaticMarkup(portals^[1].content),
      );
    },
  );

let appendPortal =
  Alcotest.test_case(
    "should append portals",
    `Quick,
    () => {
      let portals: ref(array(UniversalPortal_Shared.Portal.portal)) =
        ref([||]);

      let element =
        ReactDOM.renderToString(
          UniversalPortal_Server.collectPortals(
            <body>
              <div>
                <UniversalPortal_Shared.Portal selector="body">
                  <div> {React.string("Hello")} </div>
                </UniversalPortal_Shared.Portal>
                <UniversalPortal_Shared.Portal selector="#portal-root">
                  <div> {React.string("World!")} </div>
                </UniversalPortal_Shared.Portal>
              </div>
              <div id="portal-root" />
            </body>,
            (collectedPortal: UniversalPortal_Shared.Portal.portal) => {
            portals := Array.append(portals^, [|collectedPortal|])
          }),
        );

      let html =
        UniversalPortal_Server.appendUniversalPortals(element, portals^);

      Alcotest.(check(string))(
        "portal selector",
        "<body><div></div><div id=\"portal-root\"><div data-universal-portal=\"\">World!</div></div><div data-universal-portal=\"\">Hello</div></body>",
        html,
      );
    },
  );

let tests = ("Server", [collectPortal, appendPortal]);
