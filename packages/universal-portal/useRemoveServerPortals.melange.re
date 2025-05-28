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

let make = () => {
  React.useEffect1(
    () => {
      removeServerPortals();

      None;
    },
    [||],
  );
};
