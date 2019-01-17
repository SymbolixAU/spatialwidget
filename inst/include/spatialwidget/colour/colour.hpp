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

  inline bool is_in( const char* x, Rcpp::CharacterVector v ) {
    int n = v.size();
    int i;
    for( i = 0; i < n; i++ ) {
      if( v[i] == x ) {
        return true;
      }
    }
    return false;
  }

  template < int RTYPE >
  inline Rcpp::CharacterVector rClass( Rcpp::Vector< RTYPE > v ) {
    if( Rf_isNull( v.attr("class")) ) {
      return "";
    }
    return v.attr("class");
  }

  inline Rcpp::CharacterVector getRClass( SEXP obj ) {

    switch( TYPEOF( obj ) ) {
    case REALSXP:
      return rClass< REALSXP >( obj );
      //return "numeric";
    case VECSXP:
      return rClass< VECSXP >( obj );
      //return "character";
    case INTSXP:
      return rClass< INTSXP >( obj );
      //return "numeric";
    case LGLSXP:
      //return rClass< LGLSXP >( obj );
      return "logical";
    case STRSXP:
      //return rClass< STRSXP >( obj );
      return "character";
    }
    return "";
  }

  inline Rcpp::List make_colours(
      Rcpp::List& lst_params,
      Rcpp::List& params,
      Rcpp::DataFrame& data,
      Rcpp::List& lst_defaults,
      int col_index,
      SEXP& palette_type,
      Rcpp::NumericVector& alpha,
      std::string& colour_name,
      bool& include_legend) {

    std::string na_colour = params.containsElementNamed( "na_colour" ) ?
    params["na_colour"] : default_na_colour;

    bool include_alpha = true;            // always true - deck.gl supports alpha

    SEXP pal = spatialwidget::palette::resolve_palette( lst_params, params );

    std::string format_type;

    if ( col_index == -1 ) {

      palette_type = lst_defaults[ colour_name.c_str() ];
      //format_type = "numeric";

    } else {
      Rcpp::String this_colour = params[ colour_name.c_str() ];

      // Rcpp::StringVector sv_r_type;
      // Rcpp::String rs_format_type;
      //
      // sv_r_type = data_types[ this_colour ];
      // rs_format_type = sv_r_type[0];
      // format_type = rs_format_type;
    }

    switch ( TYPEOF( palette_type ) ) {
    case STRSXP: {} // string vector
    case LGLSXP: {  // logical vector
      Rcpp::StringVector colour_vec = Rcpp::as< Rcpp::StringVector >( palette_type );
      // TODO( if colour_vec is hex_strings, assume the user passed-in the colours they want to use? )
      Rcpp::String first_colour = colour_vec[0];
      std::string first_colour_str = first_colour;
      if ( spatialwidget::utils::colour::is_hex( first_colour_str ) ) {

        Rcpp::StringVector lvls = Rcpp::unique( colour_vec );

        Rcpp::List legend = Rcpp::List::create(
          _["colours"] = colour_vec,
          _["summary_values"] = lvls,
          _["summary_colours"] = lvls
        );

        if ( include_legend ) {
          legend[ "colour_type" ] = colour_name;
          legend[ "type" ] = "category";
        }
        return legend;

      } else {
        Rcpp::List legend = spatialwidget::palette::colour_with_palette( pal, colour_vec, alpha, na_colour, include_alpha, colour_name );

        if ( include_legend ) {
          legend[ "colour_type" ] = colour_name;
          legend[ "type" ] = "category";
        }
        return legend;
      }
      break;
    }
    default: {

      Rcpp::CharacterVector cls = getRClass( palette_type );
      if( is_in( "Date", cls ) ) {
        format_type = "Date";
      } else if ( is_in("POSIXct", cls) ) {
        format_type = "POSIXct";
      } else if ( is_in("logical", cls) ) {
        format_type = "logical";
      } else if ( is_in("character", cls) ) {
        format_type = "character";
      } else {
        format_type = "numeric";
      }

      Rcpp::NumericVector colour_vec = Rcpp::as< Rcpp::NumericVector >( palette_type );
      Rcpp::List legend = spatialwidget::palette::colour_with_palette( pal, colour_vec, alpha, na_colour, include_alpha, colour_name, format_type );

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
      Rcpp::List& lst_defaults,
      std::string& colour_name,
      std::string& opacity_name,
      Rcpp::List& lst_legend,
      bool& include_legend ) {

    Rcpp::IntegerVector data_column_index = lst_params[ "data_column_index" ];
    Rcpp::IntegerVector parameter_type = lst_params[ "parameter_type" ];
    Rcpp::StringVector param_names = params.names();

    Rcpp::StringVector hex_strings( data.nrows() );

    Rcpp::NumericVector alpha( 1, 255.0 ); // can be overwritten by user

    SEXP this_colour;

    int colour_location = spatialwidget::utils::where::where_is( colour_name, param_names );
    int opacity_location = spatialwidget::utils::where::where_is( opacity_name, param_names );

    // if 'colour_name' doesn't exist in the list of default, we need to make one

    int colourColIndex = colour_location >= 0 ? data_column_index[ colour_location ] : -1;
    int alphaColIndex = opacity_location >= 0 ? data_column_index[ opacity_location ] : -1;

    if ( colourColIndex >= 0 ) {
      this_colour = data[ colourColIndex ];
    } else {

      if ( colour_location >= 0 ) {

        SEXP val = params[ colour_location ];
        int n = data.nrows();
        Rcpp::String col_name = colour_name;
        spatialwidget::utils::fill::fill_vector( lst_defaults, col_name, val, n );

      } else {
        Rcpp::NumericVector nv( data.nrows(), 1.0 );
        this_colour = nv;
        lst_defaults[ colour_name.c_str() ] = nv; // need to add back to lst_defaults
      }
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

    Rcpp::List legend = make_colours(
      lst_params, params, data, lst_defaults, colourColIndex, //data_column_index, //hex_strings,
      this_colour, alpha, colour_name, include_legend
    );

    // this can't be replaced with 'include_legend'
    bool make_legend = false;

    if ( lst_legend.containsElementNamed( colour_name.c_str() ) ) {
      make_legend = lst_legend[ colour_name.c_str() ];
    }

    lst_defaults[ colour_name.c_str() ] = legend[ "colours" ];

    if (lst_legend.containsElementNamed( colour_name.c_str() ) ) {

      if (  make_legend == true ) {

        SEXP t = params[ colour_name ];
        Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( t );
        Rcpp::String s = sv[0];
        std::string title = s;
        std::string css = "";

        if ( params.containsElementNamed("legend_options") ) {

          Rcpp::List opts = params[ "legend_options" ];
          std::string title_string = "title";
          std::string css_string = "css";
          spatialwidget::legend::set_legend_option( opts, title_string, title, colour_name );
          spatialwidget::legend::set_legend_option( opts, css_string, css, colour_name );
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
