type portal = {
  selector: string,
  content: React.element,
};
let portalCollectorContext = React.createContext((_: portal) => ());

[@react.component]
let make = (~children, ~selector) => {
  let context = React.useContext(portalCollectorContext);
  let (portalNode, setPortalNode) = React.useState(() => None);

  let createPortal = domElement =>
    ReactDOM.createPortal(children, domElement);

  React.useEffect1(
    () => {
      let domElement = ReactDOM.querySelector(selector);
      setPortalNode(_ => domElement);

      None;
    },
    [||],
  );

  switch%platform (Runtime.platform) {
  | Client =>
    // Portal doesn't need to be collected on the client
    context
    |> ignore
  | Server => context({selector, content: children})
  };

  switch (portalNode) {
  | Some(node) => createPortal(node)
  | _ => React.null
  };
};
