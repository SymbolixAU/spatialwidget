#ifndef R_SPATIALWIDGET_COLOUR_H
#define R_SPATIALWIDGET_COLOUR_H

#include <Rcpp.h>
#include "spatialwidget/palette/palette.hpp"
#include "spatialwidget/utils/utils.hpp"
#include "spatialwidget/legend/legend.hpp"

namespace spatialwidget {
namespace colour {

  inline Rcpp::List make_colours(
      Rcpp::List& lst_params,
      Rcpp::List& params,
      Rcpp::DataFrame& data,
      Rcpp::List& data_types,
      Rcpp::List& lst_defaults,
      Rcpp::IntegerVector& data_column_index,
      SEXP& palette_type,                // string or matrix
      Rcpp::NumericVector& alpha,
      const char* colour_name,
      bool include_legend) {

    std::string na_colour = params.containsElementNamed("na_colour") ? params["na_colour" ] : spatialwidget::palette::default_na_colour;
    bool include_alpha = true;            // always true - deck.gl supports alpha

    SEXP pal = spatialwidget::palette::resolve_palette( lst_params, params );

    // TODO( can I get the legend data type from here? - if so, we can specify a 'foramt_type" for the legend formatting)
    // Rcpp::Rcout << "palette type: " << TYPEOF( palette_type ) << std::endl;
    // Rcpp::StringVector data_type_names = data_types.names();
    // Rcpp::Rcout << "data_types: " << data_type_names << std::endl;
    // Rcpp::StringVector data_names = data.names();
    // Rcpp::Rcout << "colour_name: " << colour_name << std::endl;

    // Rcpp::Rcout << "data_column_index: " << data_column_index << std::endl;
    // Rcpp::StringVector this_name = data_names[ data_column_index ];

    Rcpp::String this_colour = params[ colour_name ];

    // Rcpp::String this_c_name = this_name[0];
    Rcpp::StringVector sv_r_type = data_types[ this_colour ];

    //Rcpp::StringVector sv_r_type = Rcpp::as< Rcpp::StringVector >( r_type );
    // Rcpp::Rcout << "r_type: " << sv_r_type << std::endl;
    Rcpp::String rs_format_type = sv_r_type[0];
    std::string format_type = rs_format_type;
    // TODO( if the format-type is unsupported )

    switch ( TYPEOF( palette_type ) ) {
    case 16: {
      Rcpp::StringVector colour_vec = Rcpp::as< Rcpp::StringVector >( palette_type );
      Rcpp::List legend = spatialwidget::palette::colour_with_palette( pal, colour_vec, alpha, na_colour, include_alpha );
      if ( include_legend ) {
        legend[ "colour_type" ] = colour_name;
        legend[ "type" ] = "category";
      }
      return legend;
      break;
    }
    default: {
      Rcpp::NumericVector colour_vec = Rcpp::as< Rcpp::NumericVector >( palette_type );
      // Rcpp::Rcout << "colour_vec: " << colour_vec << std::endl;
      Rcpp::List legend = spatialwidget::palette::colour_with_palette( pal, colour_vec, alpha, na_colour, include_alpha, format_type );
      //Rcpp::StringVector colours = legend["colours"];
      //Rcpp::Rcout << "colours: " << colours << std::endl;

      // TODO( the summary values will be dependant on the type of formatting! )
      // Rcpp::StringVector summary = legend["summary_values"];
      // Rcpp::Rcout << "summary" << summary << std::endl;

      if ( include_legend ) {
        legend[ "colour_type" ] = colour_name;
        legend[ "type" ] = "gradient";
      }
      return legend;
      break;
    }
    }
  }

  inline void resolve_colour(
      Rcpp::List& lst_params,
      Rcpp::List& params,
      Rcpp::DataFrame& data,
      Rcpp::List& data_types,      // the R data types (class) of `data`
      Rcpp::List& lst_defaults,
      const char* colour_name,
      const char* opacity_name,
      Rcpp::List& lst_legend,
      bool include_legend ) {

    Rcpp::IntegerVector data_column_index = lst_params[ "data_column_index" ];
    Rcpp::IntegerVector parameter_type = lst_params[ "parameter_type" ];
    Rcpp::StringVector param_names = params.names();

    Rcpp::StringVector hex_strings( data.nrows() );

    Rcpp::NumericVector alpha( 1, 255.0 ); // can be overwritten by user

    SEXP this_colour = lst_defaults[ colour_name ];

    int colour_location = spatialwidget::utils::where_is( colour_name, param_names );
    int opacity_location = spatialwidget::utils::where_is( opacity_name, param_names );

    int colourColIndex = colour_location >= 0 ? data_column_index[ colour_location ] : -1;
    int alphaColIndex = opacity_location >= 0 ? data_column_index[ opacity_location ] : -1;

    if ( colourColIndex >= 0 ) {
      this_colour = data[ colourColIndex ];
    } else {
      // TODO ( if it's a hex string, apply it to all rows of data )
      // i.e., when not a column of data, but ISS a hex string
      // so this will be
      // } else if (is_hex_string() ) {
      // Rcpp::StringVector hex( data_rows, hex );
      //}
    }

    if ( alphaColIndex >= 0 ) {
      alpha = data[ alphaColIndex ];
    } else {

      int find_opacity = spatialwidget::utils::where_is( opacity_name, param_names );
      if (find_opacity >= 0 ) {
        int a = params[ find_opacity ]; // will throw an error if not correct type
        alpha.fill( a );
      }
    }

    Rcpp::List legend = make_colours(
      lst_params, params, data, data_types, lst_defaults, data_column_index, //hex_strings,
      this_colour, alpha, colour_name, include_legend
    );

    // TODO( can this be replaced with 'include_legend') ?
    // NO!
    bool make_legend;
    if ( lst_legend.containsElementNamed( colour_name ) ) {
      make_legend = lst_legend[ colour_name ];
    }

    lst_defaults[ colour_name ] = legend[ "colours" ];

    if (lst_legend.containsElementNamed( colour_name ) ) {

      if (  make_legend == true ) {

        std::string title = params[ colour_name ];
        std::string css = "";

        if ( params.containsElementNamed("legend_options") ) {

          Rcpp::List opts = params[ "legend_options" ];
          spatialwidget::legend::set_legend_option( opts, "title", title, colour_name );
          spatialwidget::legend::set_legend_option( opts, "css", css, colour_name );
        }

        Rcpp::List summary = Rcpp::List::create(
          Rcpp::_["colour"] = legend[ "summary_colours" ],
          Rcpp::_["variable"] = legend[ "summary_values" ],
          Rcpp::_["colourType"] = legend[ "colour_type" ],
          Rcpp::_["type"] = legend["type"],
          Rcpp::_["title"] = title,
          Rcpp::_["css"] = css
        );
        lst_legend[ colour_name ] = summary;
      }
    }
  }


} // namespace colour
} // namespace spatialwidget

#endif
