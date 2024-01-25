module PortalCollector = {
  module Provider = {
    include React.Context;
    let make =
      React.Context.provider(UniversalPortal_Shared.portalCollectorContext);
  };

  [@react.component]
  let make =
      (~children, ~collectPortal: UniversalPortal_Shared.portal => unit) => {
    let value = {
      collectPortal;
    };

    <Provider value> children </Provider>;
  };
};

let appendUniversalPortals =
    (html, portals: array(UniversalPortal_Shared.portal)) => {
  let soup = html |> Soup.parse;

  Array.iter(
    (portal: UniversalPortal_Shared.portal) => {
      let markup = portal.content |> ReactDOM.renderToString |> Soup.parse;

      switch (soup |> Soup.select_one(portal.selector)) {
      | Some(titleNode) => Soup.append_child(titleNode, markup)
      | None => ()
      };
    },
    portals,
  );

  let elementValue = soup |> Soup.to_string;

  Str.global_replace(
    Str.regexp("data-reactroot=\"\""),
    "data-reactroot",
    elementValue,
  );
};

let collectPortals = (element, callback) => {
  <PortalCollector collectPortal={newValue => {callback(newValue)}}>
    element
  </PortalCollector>;
};
