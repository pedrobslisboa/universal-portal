module PortalCollector = {
  module Provider = {
    include React.Context;
    let make =
      React.Context.provider(UniversalPortal_Shared.Components.Portal.portalCollectorContext);
  };

  [@react.component]
  let make =
      (~children, ~collectPortal: UniversalPortal_Shared.Components.Portal.portal => unit) => {
    let value = {
      collectPortal;
    };

    <Provider value> children </Provider>;
  };
};

let appendUniversalPortals =
    (html, portals: array(UniversalPortal_Shared.Components.Portal.portal)) => {
  let soup = html |> Soup.parse;

  Array.iter(
    (portal: UniversalPortal_Shared.Components.Portal.portal) => {
      let markup = portal.content |> ReactDOM.renderToString |> Soup.parse;

      switch (soup |> Soup.select_one(portal.selector)) {
      | Some(titleNode) =>
        markup
        |> Soup.select_one(":root")
        |> Soup.require
        |> Soup.set_attribute("data-universal-portal", "");
        Soup.append_child(titleNode, markup);
      | None => ()
      };
    },
    portals,
  );

  let elementValue = soup |> Soup.to_string;

  elementValue;
};

let collectPortals = (element, callback) => {
  <PortalCollector collectPortal={newValue => {callback(newValue)}}>
    element
  </PortalCollector>;
};
