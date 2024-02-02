type element;
type nodeList;
type document;

external document: document = "document";

external querySelectorAll: string => nodeList = "document.querySelectorAll";

external slice: nodeList => array(element) = "Array.prototype.slice.call";
[@mel.send] external remove: element => unit = "remove";

let removeServerPortals = () => {
  Array.iter(
    element => {remove(element)},
    slice(querySelectorAll("[data-universal-portal]")),
  );
};

let%browser_only isClient = () => true;

let canUseDom = () =>
  try(isClient()) {
  | _ => false
  };

type portal = {
  selector: string,
  content: React.element,
};
let portalCollectorContext = React.createContext((_: portal) => ());

module Portal = {
  [@react.component]
  let make = (~children, ~selector) => {
    let context = React.useContext(portalCollectorContext);
    let (portalNode, setPortalNode) = React.useState(() => None);

    let createPortal = domElement =>
      ReactDOM.createPortal(
        children,
        domElement,
      );

    React.useEffect1(
      () => {
        let domElement = ReactDOM.querySelector(selector);
        setPortalNode(_ => domElement);

        None;
      },
      [||],
    );

    if (!canUseDom()) {
      context({selector, content: children});
    };

    switch (portalNode) {
    | Some(node) => createPortal(node)
    | _ => React.null
    };
  };
};
