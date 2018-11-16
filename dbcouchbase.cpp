#define BOOST_SPIRIT_THREADSAFE

#include "dbcouchbase.h"
#include <boost/property_tree/json_parser.hpp>


void DbCouchbase::Initialize( const std::string &configPath )
{
    ParseConfig( configPath );
    std::string cbConnstr  = "couchbase://" + config_.get<std::string>( "cb_host" ) + "/" + config_.get<std::string>( "cb_bucket" );
    std::string cbUsername = config_.get<std::string>( "cb_username" );
    std::string cbPassword = config_.get<std::string>( "cb_password" );

    db_ = std::make_shared<Couchbase::Client>( cbConnstr.c_str(), cbPassword.c_str(), cbUsername.c_str() );

    Couchbase::Status status = db_->connect();
    if ( !status.success() )
        throw std::logic_error( status.description() );

}


void DbCouchbase::Shutdown()
{
    db_.reset();
    config_.clear();
}


void DbCouchbase::Put( const std::string &key, const std::string &value )
{
    DbPtr db = db_;
    if ( db )
    {
        Couchbase::StoreResponse status = db->upsert( key, value );
        if ( !status.status().success() )
            throw std::logic_error( status.status().description() );
    }
}


void DbCouchbase::Delete( const std::string &key )
{
    DbPtr db = db_;
    if ( db )
    {
        Couchbase::RemoveResponse status = db->remove( key );
        if ( !status.status().success() )
            throw std::logic_error( status.status().description() );
    }
}


void DbCouchbase::GetAll( GetCallback callback )
{
    DbPtr db = db_;
    if ( db )
    {

        Couchbase::Status status;

        Couchbase::QueryCommand qcmd(
            "SELECT v, meta(v).id AS k FROM `" + config_.get<std::string>( "cb_bucket" ) + "` v"
        );

        Couchbase::Query q(*db, qcmd, status);
        if ( !status.success() )
            throw std::logic_error( status.description() );

        for (auto row : q) 
        {
            boost::property_tree::ptree rowtree;
            std::stringstream str;
            std::stringstream value;

            str << row.json();
            boost::property_tree::read_json( str, rowtree );
            boost::property_tree::write_json( value, rowtree.get_child("v") );

            callback ( rowtree.get<std::string>("k"), value.str() );
        }
        if ( !q.status() )
            throw std::logic_error( q.status().description() );

    }
}



void DbCouchbase::ParseConfig( const std::string &configPath )
{
    std::ifstream file( configPath.c_str() );
    if ( !file.is_open() )
        throw std::logic_error( "DbCouchbase::ParseConfig: couldn't open " + configPath );

    boost::property_tree::read_json( file, config_ );
}


common::IHistory *CreateHistory( int interfaceVersion )
{
    return interfaceVersion == common::HISTORY_VERSION ?
        new DbCouchbase : nullptr;
}

void DestroyHistory( const common::IHistory *history )
{
    delete history;
}

