// -*- C++ -*-
//
// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#include <odb/pre.hxx>

#include "dogen.relational/odb/tracing/transform_event-odb-pgsql.hxx"

#include <cassert>
#include <cstring>  // std::memcpy

#include <odb/schema-catalog-impl.hxx>

#include <odb/pgsql/traits.hxx>
#include <odb/pgsql/database.hxx>
#include <odb/pgsql/transaction.hxx>
#include <odb/pgsql/connection.hxx>
#include <odb/pgsql/statement.hxx>
#include <odb/pgsql/statement-cache.hxx>
#include <odb/pgsql/simple-object-statements.hxx>
#include <odb/pgsql/container-statements.hxx>
#include <odb/pgsql/exceptions.hxx>
#include <odb/pgsql/simple-object-result.hxx>

namespace odb
{
  // transform_event
  //

  const char access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::
  persist_statement_name[] = "PERSIST_DOGEN_RELATIONAL_TRACING_TRANSFORM_EVENT";

  const char access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::
  find_statement_name[] = "FIND_DOGEN_RELATIONAL_TRACING_TRANSFORM_EVENT";

  const char access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::
  update_statement_name[] = "UPDATE_DOGEN_RELATIONAL_TRACING_TRANSFORM_EVENT";

  const char access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::
  erase_statement_name[] = "ERASE_DOGEN_RELATIONAL_TRACING_TRANSFORM_EVENT";

  const char access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::
  query_statement_name[] = "QUERY_DOGEN_RELATIONAL_TRACING_TRANSFORM_EVENT";

  const char access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::
  erase_query_statement_name[] = "ERASE_QUERY_DOGEN_RELATIONAL_TRACING_TRANSFORM_EVENT";

  const unsigned int access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::
  persist_statement_types[] =
  {
    pgsql::timestamp_oid,
    pgsql::text_oid,
    pgsql::int4_oid,
    pgsql::text_oid,
    pgsql::int4_oid,
    pgsql::text_oid,
    pgsql::text_oid,
    pgsql::text_oid
  };

  const unsigned int access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::
  find_statement_types[] =
  {
    pgsql::text_oid,
    pgsql::int4_oid
  };

  const unsigned int access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::
  update_statement_types[] =
  {
    pgsql::timestamp_oid,
    pgsql::text_oid,
    pgsql::int4_oid,
    pgsql::text_oid,
    pgsql::text_oid,
    pgsql::text_oid,
    pgsql::text_oid,
    pgsql::int4_oid
  };

  struct access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::extra_statement_cache_type
  {
    extra_statement_cache_type (
      pgsql::connection&,
      image_type&,
      id_image_type&,
      pgsql::binding&,
      pgsql::binding&,
      pgsql::native_binding&,
      const unsigned int*)
    {
    }
  };

  access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::id_type
  access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::
  id (const image_type& i)
  {
    pgsql::database* db (0);
    ODB_POTENTIALLY_UNUSED (db);

    id_type id;
    {
      composite_value_traits< ::dogen::relational::tracing::transform_event_key, id_pgsql >::init (
        id,
        i.transform_event_key_value,
        db);
    }

    return id;
  }

  bool access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::
  grow (image_type& i,
        bool* t)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (t);

    bool grew (false);

    // timestamp_
    //
    t[0UL] = 0;

    // transform_event_key_
    //
    if (composite_value_traits< ::dogen::relational::tracing::transform_event_key, id_pgsql >::grow (
          i.transform_event_key_value, t + 1UL))
      grew = true;

    // run_id_
    //
    if (composite_value_traits< ::dogen::relational::tracing::run_id, id_pgsql >::grow (
          i.run_id_value, t + 3UL))
      grew = true;

    // transform_type_
    //
    t[4UL] = 0;

    // transform_id_
    //
    if (composite_value_traits< ::dogen::relational::tracing::transform_id, id_pgsql >::grow (
          i.transform_id_value, t + 5UL))
      grew = true;

    // payload_
    //
    if (composite_value_traits< ::dogen::relational::tracing::json, id_pgsql >::grow (
          i.payload_value, t + 6UL))
      grew = true;

    // model_id_
    //
    if (t[7UL])
    {
      i.model_id_value.capacity (i.model_id_size);
      grew = true;
    }

    return grew;
  }

  void access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::
  bind (pgsql::bind* b,
        image_type& i,
        pgsql::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace pgsql;

    std::size_t n (0);

    // timestamp_
    //
    b[n].type = pgsql::bind::timestamp;
    b[n].buffer = &i.timestamp_value;
    b[n].is_null = &i.timestamp_null;
    n++;

    // transform_event_key_
    //
    if (sk != statement_update)
    {
      composite_value_traits< ::dogen::relational::tracing::transform_event_key, id_pgsql >::bind (
        b + n, i.transform_event_key_value, sk);
      n += 2UL;
    }

    // run_id_
    //
    composite_value_traits< ::dogen::relational::tracing::run_id, id_pgsql >::bind (
      b + n, i.run_id_value, sk);
    n += 1UL;

    // transform_type_
    //
    b[n].type = pgsql::bind::integer;
    b[n].buffer = &i.transform_type_value;
    b[n].is_null = &i.transform_type_null;
    n++;

    // transform_id_
    //
    composite_value_traits< ::dogen::relational::tracing::transform_id, id_pgsql >::bind (
      b + n, i.transform_id_value, sk);
    n += 1UL;

    // payload_
    //
    composite_value_traits< ::dogen::relational::tracing::json, id_pgsql >::bind (
      b + n, i.payload_value, sk);
    n += 1UL;

    // model_id_
    //
    b[n].type = pgsql::bind::text;
    b[n].buffer = i.model_id_value.data ();
    b[n].capacity = i.model_id_value.capacity ();
    b[n].size = &i.model_id_size;
    b[n].is_null = &i.model_id_null;
    n++;
  }

  void access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::
  bind (pgsql::bind* b, id_image_type& i)
  {
    std::size_t n (0);
    pgsql::statement_kind sk (pgsql::statement_select);
    composite_value_traits< ::dogen::relational::tracing::transform_event_key, id_pgsql >::bind (
      b + n, i.id_value, sk);
  }

  bool access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::
  init (image_type& i,
        const object_type& o,
        pgsql::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace pgsql;

    bool grew (false);

    // timestamp_
    //
    {
      ::boost::posix_time::ptime const& v =
        o.timestamp ();

      bool is_null (true);
      pgsql::value_traits<
          ::boost::posix_time::ptime,
          pgsql::id_timestamp >::set_image (
        i.timestamp_value, is_null, v);
      i.timestamp_null = is_null;
    }

    // transform_event_key_
    //
    if (sk == statement_insert)
    {
      ::dogen::relational::tracing::transform_event_key const& v =
        o.transform_event_key ();

      if (composite_value_traits< ::dogen::relational::tracing::transform_event_key, id_pgsql >::init (
            i.transform_event_key_value,
            v,
            sk))
        grew = true;
    }

    // run_id_
    //
    {
      ::dogen::relational::tracing::run_id const& v =
        o.run_id ();

      if (composite_value_traits< ::dogen::relational::tracing::run_id, id_pgsql >::init (
            i.run_id_value,
            v,
            sk))
        grew = true;
    }

    // transform_type_
    //
    {
      ::dogen::relational::tracing::transform_type const& v =
        o.transform_type ();

      bool is_null (false);
      pgsql::value_traits<
          ::dogen::relational::tracing::transform_type,
          pgsql::id_integer >::set_image (
        i.transform_type_value, is_null, v);
      i.transform_type_null = is_null;
    }

    // transform_id_
    //
    {
      ::dogen::relational::tracing::transform_id const& v =
        o.transform_id ();

      if (composite_value_traits< ::dogen::relational::tracing::transform_id, id_pgsql >::init (
            i.transform_id_value,
            v,
            sk))
        grew = true;
    }

    // payload_
    //
    {
      ::dogen::relational::tracing::json const& v =
        o.payload ();

      if (composite_value_traits< ::dogen::relational::tracing::json, id_pgsql >::init (
            i.payload_value,
            v,
            sk))
        grew = true;
    }

    // model_id_
    //
    {
      ::std::string const& v =
        o.model_id ();

      bool is_null (false);
      std::size_t size (0);
      std::size_t cap (i.model_id_value.capacity ());
      pgsql::value_traits<
          ::std::string,
          pgsql::id_string >::set_image (
        i.model_id_value,
        size,
        is_null,
        v);
      i.model_id_null = is_null;
      i.model_id_size = size;
      grew = grew || (cap != i.model_id_value.capacity ());
    }

    return grew;
  }

  void access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::
  init (object_type& o,
        const image_type& i,
        database* db)
  {
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (db);

    // timestamp_
    //
    {
      ::boost::posix_time::ptime& v =
        o.timestamp ();

      pgsql::value_traits<
          ::boost::posix_time::ptime,
          pgsql::id_timestamp >::set_value (
        v,
        i.timestamp_value,
        i.timestamp_null);
    }

    // transform_event_key_
    //
    {
      ::dogen::relational::tracing::transform_event_key& v =
        o.transform_event_key ();

      composite_value_traits< ::dogen::relational::tracing::transform_event_key, id_pgsql >::init (
        v,
        i.transform_event_key_value,
        db);
    }

    // run_id_
    //
    {
      ::dogen::relational::tracing::run_id& v =
        o.run_id ();

      composite_value_traits< ::dogen::relational::tracing::run_id, id_pgsql >::init (
        v,
        i.run_id_value,
        db);
    }

    // transform_type_
    //
    {
      ::dogen::relational::tracing::transform_type v;

      pgsql::value_traits<
          ::dogen::relational::tracing::transform_type,
          pgsql::id_integer >::set_value (
        v,
        i.transform_type_value,
        i.transform_type_null);

      o.transform_type (v);
    }

    // transform_id_
    //
    {
      ::dogen::relational::tracing::transform_id& v =
        o.transform_id ();

      composite_value_traits< ::dogen::relational::tracing::transform_id, id_pgsql >::init (
        v,
        i.transform_id_value,
        db);
    }

    // payload_
    //
    {
      ::dogen::relational::tracing::json& v =
        o.payload ();

      composite_value_traits< ::dogen::relational::tracing::json, id_pgsql >::init (
        v,
        i.payload_value,
        db);
    }

    // model_id_
    //
    {
      ::std::string& v =
        o.model_id ();

      pgsql::value_traits<
          ::std::string,
          pgsql::id_string >::set_value (
        v,
        i.model_id_value,
        i.model_id_size,
        i.model_id_null);
    }
  }

  void access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::
  init (id_image_type& i, const id_type& id)
  {
    bool grew (false);
    pgsql::statement_kind sk (pgsql::statement_select);
    {
      if (composite_value_traits< ::dogen::relational::tracing::transform_event_key, id_pgsql >::init (
            i.id_value,
            id,
            sk))
        grew = true;
    }

    if (grew)
      i.version++;
  }

  const char access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::persist_statement[] =
  "INSERT INTO \"DOGEN\".\"TRANSFORM_EVENT\" "
  "(\"TIMESTAMP\", "
  "\"TRANSFORM_INSTANCE_ID\", "
  "\"EVENT_TYPE\", "
  "\"RUN_ID\", "
  "\"TRANSFORM_TYPE\", "
  "\"TRANSFORM_ID\", "
  "\"PAYLOAD\", "
  "\"MODEL_ID\") "
  "VALUES "
  "($1, $2, $3, $4, $5, $6, to_jsonb($7::jsonb), $8)";

  const char access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::find_statement[] =
  "SELECT "
  "\"DOGEN\".\"TRANSFORM_EVENT\".\"TIMESTAMP\", "
  "\"DOGEN\".\"TRANSFORM_EVENT\".\"TRANSFORM_INSTANCE_ID\", "
  "\"DOGEN\".\"TRANSFORM_EVENT\".\"EVENT_TYPE\", "
  "\"DOGEN\".\"TRANSFORM_EVENT\".\"RUN_ID\", "
  "\"DOGEN\".\"TRANSFORM_EVENT\".\"TRANSFORM_TYPE\", "
  "\"DOGEN\".\"TRANSFORM_EVENT\".\"TRANSFORM_ID\", "
  "from_jsonb(\"DOGEN\".\"TRANSFORM_EVENT\".\"PAYLOAD\"), "
  "\"DOGEN\".\"TRANSFORM_EVENT\".\"MODEL_ID\" "
  "FROM \"DOGEN\".\"TRANSFORM_EVENT\" "
  "WHERE \"DOGEN\".\"TRANSFORM_EVENT\".\"TRANSFORM_INSTANCE_ID\"=$1 AND \"DOGEN\".\"TRANSFORM_EVENT\".\"EVENT_TYPE\"=$2";

  const char access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::update_statement[] =
  "UPDATE \"DOGEN\".\"TRANSFORM_EVENT\" "
  "SET "
  "\"TIMESTAMP\"=$1, "
  "\"RUN_ID\"=$2, "
  "\"TRANSFORM_TYPE\"=$3, "
  "\"TRANSFORM_ID\"=$4, "
  "\"PAYLOAD\"=to_jsonb($5::jsonb), "
  "\"MODEL_ID\"=$6 "
  "WHERE \"TRANSFORM_INSTANCE_ID\"=$7 AND \"EVENT_TYPE\"=$8";

  const char access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::erase_statement[] =
  "DELETE FROM \"DOGEN\".\"TRANSFORM_EVENT\" "
  "WHERE \"TRANSFORM_INSTANCE_ID\"=$1 AND \"EVENT_TYPE\"=$2";

  const char access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::query_statement[] =
  "SELECT "
  "\"DOGEN\".\"TRANSFORM_EVENT\".\"TIMESTAMP\", "
  "\"DOGEN\".\"TRANSFORM_EVENT\".\"TRANSFORM_INSTANCE_ID\", "
  "\"DOGEN\".\"TRANSFORM_EVENT\".\"EVENT_TYPE\", "
  "\"DOGEN\".\"TRANSFORM_EVENT\".\"RUN_ID\", "
  "\"DOGEN\".\"TRANSFORM_EVENT\".\"TRANSFORM_TYPE\", "
  "\"DOGEN\".\"TRANSFORM_EVENT\".\"TRANSFORM_ID\", "
  "from_jsonb(\"DOGEN\".\"TRANSFORM_EVENT\".\"PAYLOAD\"), "
  "\"DOGEN\".\"TRANSFORM_EVENT\".\"MODEL_ID\" "
  "FROM \"DOGEN\".\"TRANSFORM_EVENT\"";

  const char access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::erase_query_statement[] =
  "DELETE FROM \"DOGEN\".\"TRANSFORM_EVENT\"";

  const char access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::table_name[] =
  "\"DOGEN\".\"TRANSFORM_EVENT\"";

  void access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::
  persist (database& db, const object_type& obj)
  {
    ODB_POTENTIALLY_UNUSED (db);

    using namespace pgsql;

    pgsql::connection& conn (
      pgsql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    callback (db,
              obj,
              callback_event::pre_persist);

    image_type& im (sts.image ());
    binding& imb (sts.insert_image_binding ());

    if (init (im, obj, statement_insert))
      im.version++;

    if (im.version != sts.insert_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_insert);
      sts.insert_image_version (im.version);
      imb.version++;
    }

    insert_statement& st (sts.persist_statement ());
    if (!st.execute ())
      throw object_already_persistent ();

    callback (db,
              obj,
              callback_event::post_persist);
  }

  void access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::
  update (database& db, const object_type& obj)
  {
    ODB_POTENTIALLY_UNUSED (db);

    using namespace pgsql;
    using pgsql::update_statement;

    callback (db, obj, callback_event::pre_update);

    pgsql::transaction& tr (pgsql::transaction::current ());
    pgsql::connection& conn (tr.connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    id_image_type& idi (sts.id_image ());
    init (idi, id (obj));

    image_type& im (sts.image ());
    if (init (im, obj, statement_update))
      im.version++;

    bool u (false);
    binding& imb (sts.update_image_binding ());
    if (im.version != sts.update_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_update);
      sts.update_image_version (im.version);
      imb.version++;
      u = true;
    }

    binding& idb (sts.id_image_binding ());
    if (idi.version != sts.update_id_image_version () ||
        idb.version == 0)
    {
      if (idi.version != sts.id_image_version () ||
          idb.version == 0)
      {
        bind (idb.bind, idi);
        sts.id_image_version (idi.version);
        idb.version++;
      }

      sts.update_id_image_version (idi.version);

      if (!u)
        imb.version++;
    }

    update_statement& st (sts.update_statement ());
    if (st.execute () == 0)
      throw object_not_persistent ();

    callback (db, obj, callback_event::post_update);
    pointer_cache_traits::update (db, obj);
  }

  void access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::
  erase (database& db, const id_type& id)
  {
    using namespace pgsql;

    ODB_POTENTIALLY_UNUSED (db);

    pgsql::connection& conn (
      pgsql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    id_image_type& i (sts.id_image ());
    init (i, id);

    binding& idb (sts.id_image_binding ());
    if (i.version != sts.id_image_version () || idb.version == 0)
    {
      bind (idb.bind, i);
      sts.id_image_version (i.version);
      idb.version++;
    }

    if (sts.erase_statement ().execute () != 1)
      throw object_not_persistent ();

    pointer_cache_traits::erase (db, id);
  }

  access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::pointer_type
  access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::
  find (database& db, const id_type& id)
  {
    using namespace pgsql;

    {
      pointer_type p (pointer_cache_traits::find (db, id));

      if (!pointer_traits::null_ptr (p))
        return p;
    }

    pgsql::connection& conn (
      pgsql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    statements_type::auto_lock l (sts);

    if (l.locked ())
    {
      if (!find_ (sts, &id))
        return pointer_type ();
    }

    pointer_type p (
      access::object_factory<object_type, pointer_type>::create ());
    pointer_traits::guard pg (p);

    pointer_cache_traits::insert_guard ig (
      pointer_cache_traits::insert (db, id, p));

    object_type& obj (pointer_traits::get_ref (p));

    if (l.locked ())
    {
      select_statement& st (sts.find_statement ());
      ODB_POTENTIALLY_UNUSED (st);

      callback (db, obj, callback_event::pre_load);
      init (obj, sts.image (), &db);
      load_ (sts, obj, false);
      sts.load_delayed (0);
      l.unlock ();
      callback (db, obj, callback_event::post_load);
      pointer_cache_traits::load (ig.position ());
    }
    else
      sts.delay_load (id, obj, ig.position ());

    ig.release ();
    pg.release ();
    return p;
  }

  bool access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::
  find (database& db, const id_type& id, object_type& obj)
  {
    using namespace pgsql;

    pgsql::connection& conn (
      pgsql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    statements_type::auto_lock l (sts);
    assert (l.locked ()) /* Must be a top-level call. */;

    if (!find_ (sts, &id))
      return false;

    select_statement& st (sts.find_statement ());
    ODB_POTENTIALLY_UNUSED (st);

    reference_cache_traits::position_type pos (
      reference_cache_traits::insert (db, id, obj));
    reference_cache_traits::insert_guard ig (pos);

    callback (db, obj, callback_event::pre_load);
    init (obj, sts.image (), &db);
    load_ (sts, obj, false);
    sts.load_delayed (0);
    l.unlock ();
    callback (db, obj, callback_event::post_load);
    reference_cache_traits::load (pos);
    ig.release ();
    return true;
  }

  bool access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::
  reload (database& db, object_type& obj)
  {
    using namespace pgsql;

    pgsql::connection& conn (
      pgsql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    statements_type::auto_lock l (sts);
    assert (l.locked ()) /* Must be a top-level call. */;

    const id_type& id (object_traits_impl::id (obj));
    if (!find_ (sts, &id))
      return false;

    select_statement& st (sts.find_statement ());
    ODB_POTENTIALLY_UNUSED (st);

    callback (db, obj, callback_event::pre_load);
    init (obj, sts.image (), &db);
    load_ (sts, obj, true);
    sts.load_delayed (0);
    l.unlock ();
    callback (db, obj, callback_event::post_load);
    return true;
  }

  bool access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::
  find_ (statements_type& sts,
         const id_type* id)
  {
    using namespace pgsql;

    id_image_type& i (sts.id_image ());
    init (i, *id);

    binding& idb (sts.id_image_binding ());
    if (i.version != sts.id_image_version () || idb.version == 0)
    {
      bind (idb.bind, i);
      sts.id_image_version (i.version);
      idb.version++;
    }

    image_type& im (sts.image ());
    binding& imb (sts.select_image_binding ());

    if (im.version != sts.select_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_select);
      sts.select_image_version (im.version);
      imb.version++;
    }

    select_statement& st (sts.find_statement ());

    st.execute ();
    auto_result ar (st);
    select_statement::result r (st.fetch ());

    if (r == select_statement::truncated)
    {
      if (grow (im, sts.select_image_truncated ()))
        im.version++;

      if (im.version != sts.select_image_version ())
      {
        bind (imb.bind, im, statement_select);
        sts.select_image_version (im.version);
        imb.version++;
        st.refetch ();
      }
    }

    return r != select_statement::no_data;
  }

  result< access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::object_type >
  access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::
  query (database&, const query_base_type& q)
  {
    using namespace pgsql;
    using odb::details::shared;
    using odb::details::shared_ptr;

    pgsql::connection& conn (
      pgsql::transaction::current ().connection ());

    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    image_type& im (sts.image ());
    binding& imb (sts.select_image_binding ());

    if (im.version != sts.select_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_select);
      sts.select_image_version (im.version);
      imb.version++;
    }

    std::string text (query_statement);
    if (!q.empty ())
    {
      text += " ";
      text += q.clause ();
    }

    q.init_parameters ();
    shared_ptr<select_statement> st (
      new (shared) select_statement (
        sts.connection (),
        query_statement_name,
        text,
        false,
        true,
        q.parameter_types (),
        q.parameter_count (),
        q.parameters_binding (),
        imb));

    st->execute ();
    st->deallocate ();

    shared_ptr< odb::object_result_impl<object_type> > r (
      new (shared) pgsql::object_result_impl<object_type> (
        q, st, sts, 0));

    return result<object_type> (r);
  }

  unsigned long long access::object_traits_impl< ::dogen::relational::tracing::transform_event, id_pgsql >::
  erase_query (database&, const query_base_type& q)
  {
    using namespace pgsql;

    pgsql::connection& conn (
      pgsql::transaction::current ().connection ());

    std::string text (erase_query_statement);
    if (!q.empty ())
    {
      text += ' ';
      text += q.clause ();
    }

    q.init_parameters ();
    delete_statement st (
      conn,
      erase_query_statement_name,
      text,
      q.parameter_types (),
      q.parameter_count (),
      q.parameters_binding ());

    return st.execute ();
  }
}

namespace odb
{
  static bool
  create_schema (database& db, unsigned short pass, bool drop)
  {
    ODB_POTENTIALLY_UNUSED (db);
    ODB_POTENTIALLY_UNUSED (pass);
    ODB_POTENTIALLY_UNUSED (drop);

    if (drop)
    {
      switch (pass)
      {
        case 1:
        {
          return true;
        }
        case 2:
        {
          db.execute ("DROP TABLE IF EXISTS \"DOGEN\".\"TRANSFORM_EVENT\" CASCADE");
          return false;
        }
      }
    }
    else
    {
      switch (pass)
      {
        case 1:
        {
          db.execute ("CREATE TABLE \"DOGEN\".\"TRANSFORM_EVENT\" (\n"
                      "  \"TIMESTAMP\" TIMESTAMP NULL,\n"
                      "  \"TRANSFORM_INSTANCE_ID\" TEXT NOT NULL,\n"
                      "  \"EVENT_TYPE\" INTEGER NOT NULL,\n"
                      "  \"RUN_ID\" TEXT NOT NULL,\n"
                      "  \"TRANSFORM_TYPE\" INTEGER NOT NULL,\n"
                      "  \"TRANSFORM_ID\" TEXT NOT NULL,\n"
                      "  \"PAYLOAD\" JSONB NOT NULL,\n"
                      "  \"MODEL_ID\" TEXT NOT NULL,\n"
                      "  PRIMARY KEY (\"TRANSFORM_INSTANCE_ID\",\n"
                      "               \"EVENT_TYPE\"))");
          return false;
        }
      }
    }

    return false;
  }

  static const schema_catalog_create_entry
  create_schema_entry_ (
    id_pgsql,
    "",
    &create_schema);
}

#include <odb/post.hxx>
