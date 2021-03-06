#if !defined(CETTY_BOOTSTRAP_BOOTSTRAP_H)
#define CETTY_BOOTSTRAP_BOOTSTRAP_H
/*
 * Copyright 2009 Red Hat, Inc.
 *
 * Red Hat licenses this file to you under the Apache License, version 2.0
 * (the "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at:
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */
/*
 * Copyright (c) 2010-2011 frankee zhou (frankee.zhou at gmail dot com)
 * Distributed under under the Apache License, version 2.0 (the "License").
 */

#include <string>
#include <map>

#include <boost/any.hpp>
#include "cetty/channel/ChannelFactory.h"
#include "cetty/channel/ChannelPipeline.h"
#include "cetty/channel/ChannelPipelineFactory.h"
#include "cetty/util/ExternalResourceReleasable.h"

namespace cetty { namespace channel {
class ChannelPipeline;
}}

namespace cetty { namespace bootstrap {

using namespace cetty::channel;

/**
 * A helper class which initializes a {@link Channel}.  This class provides
 * the common data structure for its subclasses which actually initialize
 * {@link Channel}s and their child {@link Channel}s using the common data
 * structure.  Please refer to {@link ClientBootstrap}, {@link ServerBootstrap},
 * and {@link ConnectionlessBootstrap} for client side, server-side, and
 * connectionless (e.g. UDP) channel initialization respectively.
 *
 * 
 * @author <a href="http://gleamynode.net/">Trustin Lee</a>
 *
 * @author <a href="mailto:frankee.zhou@gmail.com">Frankee Zhou</a>
 *
 * @apiviz.uses cetty::channel::ChannelFactory
 */

class Bootstrap : public ::cetty::util::ExternalResourceReleasable {
public:
	virtual ~Bootstrap();

    /**
     * Returns the {@link ChannelFactory} that will be used to perform an
     * I/O operation.
     *
     * @throws IllegalStateException
     *         if the factory is not set for this bootstrap yet.
     *         The factory can be set in the constructor or
     *         {@link #setFactory(ChannelFactory*)}.
     */
    const ChannelFactoryPtr& getFactory();

    /**
     * Sets the {@link ChannelFactory} that will be used to perform an I/O
     * operation.  This method can be called only once and can't be called at
     * all if the factory was specified in the constructor.
     *
     * @throws IllegalStateException
     *         if the factory is already set
     *
     * @throws NullPointerException
     *         if the factory is null
     */
    virtual void setFactory(const ChannelFactoryPtr& factory);

    /**
     * Returns the default {@link ChannelPipeline} which is cloned when a new
     * {@link Channel} is created.  {@link Bootstrap} creates a new pipeline
     * which has the same entries with the returned pipeline for a new
     * {@link Channel}.
     *
     * @return the default {@link ChannelPipeline}
     *
     * @throws IllegalStateException
     *         if {@link #setPipelineFactory(ChannelPipelineFactory)} was
     *         called by a user last time.
     */
    ChannelPipeline* getPipeline();

    /**
     * Sets the default {@link ChannelPipeline} which is cloned when a new
     * {@link Channel} is created.  {@link Bootstrap} creates a new pipeline
     * which has the same entries with the specified pipeline for a new channel.
     * <p>
     * Calling this method also sets the <tt>pipelineFactory</tt> property to an
     * internal {@link ChannelPipelineFactory} implementation which returns
     * a shallow copy of the specified pipeline.
     */
    virtual void setPipeline(ChannelPipeline* pipeline);

    /**
     * Dependency injection friendly convenience method for
     * {@link #getPipeline()} which returns the default pipeline of this
     * bootstrap as an ordered map.
     *
     * @throws IllegalStateException
     *         if {@link #setPipelineFactory(ChannelPipelineFactory)} was
     *         called by a user last time.
     */
    ChannelPipeline::ChannelHandlers getPipelineAsMap() const;

    /**
     * Dependency injection friendly convenience method for
     * {@link #setPipeline(ChannelPipeline)} which sets the default pipeline of
     * this bootstrap from an ordered map.
     *
     * @throws InvalidArgumentException
     *         if the specified map is not an ordered map
     */
    virtual void setPipelineAsMap(const ChannelPipeline::ChannelHandlers& pipelineMap);

    /**
     * Returns the {@link ChannelPipelineFactory} which creates a new
     * {@link ChannelPipeline} for each new {@link Channel}.
     *
     * @see #getPipeline()
     */
    const ChannelPipelineFactoryPtr getPipelineFactory() {
        return this->pipelineFactory;
    }

    /**
     * Sets the {@link ChannelPipelineFactory} which creates a new
     * {@link ChannelPipeline} for each new {@link Channel}.  Calling this
     * method invalidates the current <tt>pipeline</tt> property of this
     * bootstrap.  Subsequent {@link #getPipeline()} and {@link #getPipelineAsMap()}
     * calls will raise {@link IllegalStateException}.
     *
     * @see #setPipeline(ChannelPipeline*)
     * @see #setPipelineAsMap(const ChannelPipeline::ChannelHandlers&)
     */
    virtual void setPipelineFactory(const ChannelPipelineFactoryPtr& pipelineFactory);

    /**
     * Returns the options which configures a new {@link Channel} and its
     * child {@link Channel}s.  The names of the child {@link Channel} options
     * are prefixed with <tt>"child."</tt> (e.g. <tt>"child.keepAlive"</tt>).
     */
    const std::map<std::string, boost::any>& getOptions() const {
        return this->options;
    }

    /**
     * Returns the options which configures a new {@link Channel} and its
     * child {@link Channel}s.  The names of the child {@link Channel} options
     * are prefixed with <tt>"child."</tt> (e.g. <tt>"child.keepAlive"</tt>).
     */
    std::map<std::string, boost::any>& getOptions() {
        return this->options;
    }

    /**
     * Sets the options which configures a new {@link Channel} and its child
     * {@link Channel}s.  To set the options of a child {@link Channel}, prefixed
     * <tt>"child."</tt> to the option name (e.g. <tt>"child.keepAlive"</tt>).
     */
    void setOptions(const std::map<std::string, boost::any>& options) {
        this->options = options;
    }

    /**
     * Returns the value of the option with the specified key.  To retrieve
     * the option value of a child {@link Channel}, prefixed <tt>"child."</tt>
     * to the option name (e.g. <tt>"child.keepAlive"</tt>).
     *
     * @param key  the option name
     *
     * @return the option value if the option is found.
     *         <tt>empty boost::any</tt> otherwise.
     */
    boost::any getOption(const std::string& key) const;

    /**
     * Returns the value of the option with the specified key.  To retrieve
     * the option value of a child {@link Channel}, prefixed <tt>"child."</tt>
     * to the option name (e.g. <tt>"child.keepAlive"</tt>).
     *
     * @param key  the option name
     *
     * @return the pointer of the option value if the option is found.
     *         <tt>NULL</tt> otherwise.
     */
    template<typename T>
    const T* getTypedOption(const std::string& key) const {
        boost::any a = getOption(key);
        if (!a.empty()) {
            const T* t = boost::any_cast<T>(&a);
            if (NULL == t) return NULL;

            return t;
        }
        return NULL;
    }

    /**
     * Sets an option with the specified key and value.  If there's already
     * an option with the same key, it is replaced with the new value.  If the
     * specified value is <tt>empty boost::any</tt>, an existing option with 
     * the specified key is removed.  To set the option value of a child 
     * {@link Channel}, prepend <tt>"child."</tt> to the option name 
     * (e.g. <tt>"child.keepAlive"</tt>).
     *
     * @param key    the option name
     * @param value  the option value
     */
    virtual void setOption(const std::string& key, const boost::any& value);

    /**
     * {@inheritDoc}  This method simply delegates the call to
     * {@link ChannelFactory#releaseExternalResources()},
     * and delete the ChannelFactory, but the ChannelPipeline or
     * the ChannelPipelineFactory which set by user.
     */
    virtual void releaseExternalResources();

protected:
	/**
     * Creates a new instance with no {@link ChannelFactory} set.
     * {@link #setFactory(ChannelFactory)} must be called at once before any
     * I/O operation is requested.
     */
    Bootstrap();

    /**
     * Creates a new instance with the specified initial {@link ChannelFactory}.
     */
    Bootstrap(const ChannelFactoryPtr& channelFactory);

private:
    // indicate whether PipelineFactory is set by external or not.
    bool externalSetPipelineFactory;

    std::map<std::string, boost::any> options;

    ChannelPipeline*  pipeline;
	ChannelFactoryPtr factory;
	ChannelPipelineFactoryPtr pipelineFactory;
};

}}

#endif //#if !defined(CETTY_BOOTSTRAP_BOOTSTRAP_H)
