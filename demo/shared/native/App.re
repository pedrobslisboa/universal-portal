[@react.component]
let make = () => {
  React.useEffect1(
    () => {
      UniversalPortal_Shared.removeServerPortals();

      None;
    },
    [||],
  );

  <div>
    <UniversalPortal_Shared.Portal selector="body">
      <div
        style={ReactDOM.Style.make(
          ~position="absolute",
          ~top="0",
          ~left="0",
          ~width="100%",
          ~backgroundColor="rgba(0, 0, 0, 0.3)",
          ~height="100%",
          ~display="flex",
          ~justifyContent="center",
          ~alignItems="center",
          (),
        )}>
        <div
          style={ReactDOM.Style.make(
            ~backgroundColor="white",
            ~padding="30px",
            ~width="200px",
            ~height="200px",
            (),
          )}>
          {"Hey, I'm a portal, disable JS on your dev tools and check that I'll still here"
           |> React.string}
        </div>
      </div>
    </UniversalPortal_Shared.Portal>
  </div>;
};
