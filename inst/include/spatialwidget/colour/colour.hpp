#ifndef R_SPATIALWIDGET_COLOUR_H
#define R_SPATIALWIDGET_COLOUR_H

#include <Rcpp.h>
#include "spatialwidget/palette/palette.hpp"
#include "spatialwidget/utils/utils.hpp"
#include "spatialwidget/utils/where/where.hpp"
#include "spatialwidget/legend/legend.hpp"

namespace spatialwidget {
namespace colour {

  const std::string default_na_colour = "#808080FF";

  inline Rcpp::List make_colours(
      Rcpp::List& lst_params,
      Rcpp::List& params,
      Rcpp::DataFrame& data,
      Rcpp::List& data_types,
      Rcpp::List& lst_defaults,
      int col_index,
      //Rcpp::IntegerVector& data_column_index,
      SEXP& palette_type,
      Rcpp::NumericVector& alpha,
      const char* colour_name,
      bool include_legend) {

    // Rcpp::Rcout << "include_legend: " << include_legend << std::endl;

    std::string na_colour = params.containsElementNamed( "na_colour" ) ?
    params["na_colour" ] :
    default_na_colour;

    bool include_alpha = true;            // always true - deck.gl supports alpha

    SEXP pal = spatialwidget::palette::resolve_palette( lst_params, params );

    //Rcpp::Rcout << "data_column_index: " << data_column_index << std::endl;
    //Rcpp::StringVector this_name = data_names[ data_column_index ];

    // TODO( if the colour_name wasn't passed in as a paramter (e.g. stroke_colour),
    // need to use the default)

    std::string format_type;

    if ( col_index == -1 ) {
      //Rcpp::stop( "I still need to work out how to use the default colour");

      // Rcpp::Rcout << "using default colours: " << colour_name << std::endl;

      palette_type = lst_defaults[ colour_name ];
      format_type = "numeric";

    } else {
      Rcpp::String this_colour = params[ colour_name ];
      // Rcpp::Rcout << "this_colour: " << this_colour.get_cstring() << std::endl;

      Rcpp::StringVector sv_r_type;
      Rcpp::String rs_format_type;

      sv_r_type = data_types[ this_colour ];
      rs_format_type = sv_r_type[0];
      format_type = rs_format_type;
    }

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
      //Rcpp::Rcout << "colour_vec: " << colour_vec << std::endl;
      Rcpp::List legend = spatialwidget::palette::colour_with_palette( pal, colour_vec, alpha, na_colour, include_alpha, format_type );

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

    int colour_location = spatialwidget::utils::where::where_is( colour_name, param_names );
    int opacity_location = spatialwidget::utils::where::where_is( opacity_name, param_names );

    int colourColIndex = colour_location >= 0 ? data_column_index[ colour_location ] : -1;
    int alphaColIndex = opacity_location >= 0 ? data_column_index[ opacity_location ] : -1;

    // Rcpp::Rcout << "colourColIndex: " << colourColIndex << std::endl;
    // Rcpp::Rcout << "alphaColIndex: " << alphaColIndex << std::endl;

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

      int find_opacity = spatialwidget::utils::where::where_is( opacity_name, param_names );
      if (find_opacity >= 0 ) {
        int a = params[ find_opacity ]; // will throw an error if not correct type
        alpha.fill( a );
      }
    }

    // Rcpp::Rcout << "going to make the legend " << std::endl;
    // Rcpp::Rcout << "include_legend: " << include_legend << std::endl;

    Rcpp::List legend = make_colours(
      lst_params, params, data, data_types, lst_defaults, colourColIndex, //data_column_index, //hex_strings,
      this_colour, alpha, colour_name, include_legend
    );

    // Rcpp::Rcout << "made the legend " << std::endl;

    // TODO( can this be replaced with 'include_legend') ?
    // NO!
    bool make_legend;
    // Rcpp::Rcout << "make_legend: " << make_legend << std::endl;

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
