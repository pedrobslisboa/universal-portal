type portal = {
  selector: string,
  content: React.element,
};
let portalCollectorContext = React.createContext((_: portal) => ());

// Js component that renders a portal
[@platform js]
include {
          [@react.component]
          let make = (~children, ~selector) => {
            let (portalNode, setPortalNode) = React.useState(() => None);

            let createPortal = domElement =>
              ReactDOM.createPortal(children, domElement);

            React.useEffect(() => {
              let domElement = ReactDOM.querySelector(selector);
              setPortalNode(_ => domElement);

              None;
            });

            switch (portalNode) {
            | Some(node) => createPortal(node)
            | _ => React.null
            };
          };
        };

// Native component that collects the portals
[@platform native]
include {
          [@react.component]
          let make = (~children, ~selector) => {
            let context = React.useContext(portalCollectorContext);

            context({selector, content: children});

            React.null;
          };
        };
